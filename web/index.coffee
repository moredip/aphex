path = require('path')
fs = require('fs')
jade = require('jade')
express = require('express')
coffee = require('coffee-script')

Aphex = require( './aphex' )

getLightTty = ->
  tty = process.argv[2]
  unless tty
    process.stderr.write("please specify the device file for the serial port your device is connected to\n")
    process.stderr.write("running `ls -l /dev/tty*usb*` will probably show you some candidates\n")
    process.exit(1)
  tty

app = express()

app.use(express.bodyParser())

views =
  index: jade.compile """
    doctype 5
    html(lang="en")
      head 
        link(rel='stylesheet',href='jquery-ui-1.10.3.custom.min.css')
        link(rel='stylesheet',href='screen.css')
        script(src='jquery-1.9.1.min.js')
        script(src='jquery-ui-1.10.3.custom.min.js')
        script(src='client.js')
      body
        h1 color mixing
        hr
        #sliders
          #red
            .slider
            .number
          #green
            .slider
            .number
          #blue
            .slider
            .number
        #swatch.ui-widget-content.ui-corner-all
  """

app.get '/', (req, res)->
  res.send( 200, views.index() )

app.get '/client.js', (req,res)->
  res.header('Content-Type', 'application/javascript')
  cs = fs.readFileSync( "#{__dirname}/client.coffee", 'utf8' )
  res.send( coffee.compile(cs) )

for staticFile in ['jquery-1.9.1.min.js','jquery-ui-1.10.3.custom.min.js','jquery-ui-1.10.3.custom.min.css','screen.css']
  do (staticFile)->
    app.get "/#{staticFile}", (req, res)->
      res.sendfile("#{__dirname}/#{staticFile}")

startApp = (light)->
  app.post '/change-color/:color', (req,res)->
    newColor = req.params.color
    light.changeColor(newColor)
    res.send( 200, '' )

  app.listen(3000)
  console.log('Listening on port 3000')

Aphex.connectToLight getLightTty(), startApp
#startApp()

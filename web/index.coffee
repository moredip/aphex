path = require('path')
fs = require('fs')
jade = require('jade')
express = require('express')
coffee = require('coffee-script')
app = express()

views =
  index: jade.compile """
    doctype 5
    html(lang="en")
      head 
        link(rel='stylesheet',href='spectrum.css')
        script(src='jquery-1.9.1.min.js')
        script(src='spectrum.js')
        script(src='client.js')
      body
        h1 Aphex!
        h2 Pick a color
        input(type='color',name='color',value='#ff009c')

  """

app.get '/', (req, res)->
  res.send( 200, views.index() )

app.get '/client.js', (req,res)->
  res.header('Content-Type', 'application/javascript')
  cs = fs.readFileSync( "#{__dirname}/client.coffee", 'utf8' )
  res.send( coffee.compile(cs) )

for staticFile in ['jquery-1.9.1.min.js','spectrum.js','spectrum.css']
  do (staticFile)->
    app.get "/#{staticFile}", (req, res)->
      res.sendfile("#{__dirname}/#{staticFile}")

app.listen(3000)
console.log('Listening on port 3000')

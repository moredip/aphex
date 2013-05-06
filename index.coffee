serialport = require('serialport')
SerialPort = serialport.SerialPort

console = require('console')

tty = process.argv[2]
unless tty
  process.stderr.write("please specify the device file for the serial port your device is connected to\n")
  process.stderr.write("running `ls -l /dev/tty*usb*` will probably show you some candidates\n")
  process.exit(1)


randomColor = ->
  randomComponent = ->
    number = Math.floor(Math.random() * 255)
    asHex = number.toString(16)
    if asHex.length == 1 then ('0'+asHex) else asHex

  red = randomComponent()
  blue = randomComponent()
  green = randomComponent()
  red+blue+green


requestRandomColor = (serialPort)->
  color = randomColor()
  console.log( 'sending ' + color )
  serialPort.write color


letsGo = (serialPort)->
  console.log("Let's GO!")
  serialPort.on 'data', (data)->
    console.log("    > #{data}")

  setInterval( (->requestRandomColor(serialPort)), 100 )


do ->
  serialPort = new SerialPort(
    tty, 
    {baudrate: 57600, parser: serialport.parsers.readline("\n") }, 
    false
  )

  serialPort.open ->
    console.log('open')

    # apparently the board will drop the first few bytes as junk. Let's send it some junk.
    serialPort.write('crap'*20)

    setTimeout( (-> letsGo(serialPort)), 500 )

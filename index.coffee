SerialPort = require('serialport').SerialPort
console = require('console')

tty = process.argv[2]
unless tty
  process.stderr.write("please specify the device file for the serial port your device is connected to\n")
  process.stderr.write("running `ls -l /dev/tty*usb*` will probably show you some candidates\n")
  process.exit(1)

letsGo = (serialPort)->
  console.log("Let's GO!")
  serialPort.on 'data', (data)->
    console.log('data received: ' + data)

  serialPort.write "aaff88", (err,results)->
    console.log('err ' + err)
    console.log('results ' + results)

do ->
  serialPort = new SerialPort tty, {baudrate: 57600}, false
  serialPort.open ->
    console.log('open')

    # apparently the board will drop the first few bytes as junk. Let's send it some junk.
    serialPort.write('crap'*20)

    setTimeout( (-> letsGo(serialPort)), 500 )

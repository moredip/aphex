SP = require('serialport')
SerialPort = SP.SerialPort

createAphex = (serialPort)->
  serialPort.on 'data', (data)->
    console.log("    light said:\n  #{data}")

  changeColor = (hexRgb)->
    console.log("changing color to: #{hexRgb}")
    serialPort.write( hexRgb )

  { changeColor }

module.exports.connectToLight = (tty, onceConnected)->
  serialPort = new SerialPort(
    tty, 
    {baudrate: 57600, parser: SP.parsers.readline("\n") }, 
    false
  )

  connected = (serialPort)->
    console.log('...connected')
    aphex = createAphex(serialPort)
    onceConnected( aphex )

  serialPort.open ->
    console.log('connecting to light...')

    # apparently the board will drop the first few bytes as junk. Let's send it some junk.
    serialPort.write('junk '*20)

    setTimeout( (-> connected(serialPort)), 500 )

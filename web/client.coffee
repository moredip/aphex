intToTwoDigitHex = (i)->
  hex = i.toString(16)
  if hex.length == 1 then "0"+hex else hex

hexFromRGB = (r, g, b)->
  [
    intToTwoDigitHex(r),
    intToTwoDigitHex(g),
    intToTwoDigitHex(b)
  ].join("")

updateSwatch = (hex)->
  $( "#swatch" ).css( "background-color", "#" + hex )

updateAphex = (color)->
  $.post( "/change-color/#{color}" )
    .done( -> console.log( 'successful color update to ', color ) )
    .fail( -> console.log( 'failed to change color to ', color ) )

colorSelected = ->
  red = $( "#red" ).slider( "value" )
  green = $( "#green" ).slider( "value" )
  blue = $( "#blue" ).slider( "value" )
  hex = hexFromRGB( red, green, blue )

  updateSwatch(hex)
  updateAphex(hex)

# based on http://jqueryui.com/slider/#colorpicker

$ ->
  $( "#red, #green, #blue" ).slider(
    orientation: "horizontal"
    range: "min"
    max: 255
    slide: colorSelected
    change: colorSelected
  )
  $( "#red" ).slider( "value", 255 )
  $( "#green" ).slider( "value", 140 )
  $( "#blue" ).slider( "value", 60 )

$ -> 
  $('#custom-color-picker').spectrum
    color: '#ff009c'
    flat: true
    move: (color)->
      color = color.toHex()
      $.post( "/change-color/#{color}" )
        .done( -> console.log( 'successful color update to ', color ) )
        .fail( -> console.log( 'failed to change color to ', color ) )

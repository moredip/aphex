$ -> 
  $('#color-picker').on 'change', ()->
    color = @value.replace('#','')
    $.post( "/change-color/#{color}" )
      .done( -> console.log( 'successful color update to ', color ) )
      .fail( -> console.log( 'failed to change color to ', color ) )

jQuery ->
  $('#statement_schoolkid_id').parent().hide()
  schoolkid = $('#statement_schoolkid_id').html()
  $('#statement_group_id').change ->
    group = $('#statement_group_id :selected').text()
    options = $(schoolkid).filter("optgroup[label='#{group}']").html() 
    if options
      $('#statement_schoolkid_id').html(options)
      $('#statement_schoolkid_id').parent().show()
    else
      $('#statement_schoolkid_id').empty()
      $('#statement_schoolkid_id').parent().hide()
      
       	

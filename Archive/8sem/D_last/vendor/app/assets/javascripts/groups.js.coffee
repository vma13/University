jQuery ->
  $('#group_course_id').parent().hide()
  course = $('#group_course_id').html()
  $('#group_discipline_id').change ->
    discipline = $('#group_discipline_id :selected').text()
    options = $(course).filter("optgroup[label='#{discipline}']").html() 
    if options
      $('#group_course_id').html(options)
      $('#group_course_id').parent().show()
    else
      $('#group_course_id').empty()
      $('#group_course_id').parent().hide()
      
       	
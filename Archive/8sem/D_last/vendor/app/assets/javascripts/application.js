//= require jquery
//= require jquery_ujs
//= require_tree .

$.fn.change_year=function() {
    var year = parseInt($(this).val());
    $.post("/schoolkids/change_session_year.js", {chosen_year: year},null,'script');
    $(this).closest(".box").find(".hint").html(year);
};

$(function() {
    $("#move_data").click(function() { 
        var table = document.getElementById('rightTable');
        var index = table.getElementsByTagName('input');
        var id = document.getElementById('group_id').value;
        var arr = new Array(index.length-1);
        for( i = 1; i <= arr.length; i++) 
            arr[i-1] = index[i].value;
        $.post("save_data", {id: id, ids: arr});
        alert ("Данные сохранены.");
        return false;
    });
});

function check_all(table_id) {
    var table = document.getElementById(table_id);
    var arr = table.getElementsByTagName('input');
    if( arr[0].checked )
	for( i = 1; i < arr.length; i++)
	    arr[i].checked = true;
    else
	for( i = 1; i < arr.length; i++)
	    arr[i].checked = false;
}


function move_value(table_in, table_out) {
    var table = document.getElementById(table_in);
    var table2 = document.getElementById(table_out);
    var arr = table.getElementsByTagName('input');
    var last_index = table2.rows.length;
    for(i = arr.length-1, count = 0; i >= 1; i--) 
	if( arr[i].checked ) 
    {
        var index = arr[i].parentNode.parentNode.sectionRowIndex;
        arr[i].checked = false;
        var row = table2.insertRow( last_index++ );
        row.appendChild( arr[i].parentNode );
        table.deleteRow( index );
    }
}


$(function() {
    var dates = $( "#start_date, #end_date" ).datepicker({
        defaultDate: "+1w",
        changeMonth: true,
        numberOfMonths: 1,
        buttonImageOnly: true,
        changeYear: true,
        showButtonPanel: true,
        onSelect: function( selectedDate ) {
            var option = this.id == "start_date" ? "minDate" : "maxDate",
            instance = $( this ).data( "datepicker" ),
            date = $.datepicker.parseDate(
                instance.settings.dateFormat ||
                    $.datepicker._defaults.dateFormat,
                selectedDate, instance.settings );
            dates.not( this ).datepicker( "option", option, date );
        }
    });
});

$(function() {
    $( "#accordion" ).accordion({
	autoHeight: false,
	navigation: true,
	active: false,
	animated: 'bounceslide',
	collapsible: true
    });
});

function remove_fields(link) {
  $(link).previous("input[type=hidden]").value = "1";
  $(link).up(".fields").hide();
}

function add_fields(link, association, content) {
  var new_id = new Date().getTime();
  var regexp = new RegExp("new_" + association, "g")
  $(link).up().insert({
    before: content.replace(regexp, new_id)
  });
}

function select_table_row(table_id, row_number) {
    var table = document.getElementById(table_id);
    var arr = table.getElementsByTagName('input');
    var offset = table.rows.length;
    for (i = parseInt(row_number); i < arr.length; i += offset)
        if( arr[i].checked )
	    arr[i].checked = false;
        else
            arr[i].checked = true;
}

/*function select_table_row(table_id, row_number) {
    var table = document.getElementById(table_id);
    var arr = table.getElementsByTagName('input');
    var offset = table.rows.length;
    var i = parseInt(row_number);
    var flag;
    if ( arr[i].checked )
      flag = true;
    else
      flag = false;
    for (; i < arr.length; i += offset)
        if( !flag )
	      arr[i].checked = false;
        else
          arr[i].checked = true;
}
*/

$(function() {
    var dates = $( "#statement_start, #statement_finish" ).datepicker({
        defaultDate: "+1w",
        changeMonth: true,
        numberOfMonths: 1,
        buttonImageOnly: true,
        changeYear: true,
        showButtonPanel: true,
        onSelect: function( selectedDate ) {
            var option = this.id == "statement_start" ? "minDate" : "maxDate",
            instance = $( this ).data( "datepicker" ),
            date = $.datepicker.parseDate(
                instance.settings.dateFormat ||
                    $.datepicker._defaults.dateFormat,
                selectedDate, instance.settings );
            dates.not( this ).datepicker( "option", option, date );
        }
    });
});

$(function() {
    $("#schoolkid_school_group_tokens").tokenInput("/school_groups.json", {
        crossDomain: false,
        propertyToSearch: "number",
        resultsFormatter: function(item){return "<li>" + item.number + ",  " + item.year + "</li>"},
        tokenFormatter: function(item){return "<li><p>"+ item.number + ",  "+item.year+"</p></li>"},
        prePopulate: $("#schoolkid_school_group_tokens").data("pre"),
        theme: 'facebook',
        hintText: 'Введите класс',
        noResultsText: 'Не найдено',
        searchingText: "Поиск...",
        tokenLimit: "1"
    });
});

$(function() {
    var dates = $( "#schoolkid_birthday" ).datepicker({
        defaultDate: "+1w",
        changeMonth: true,
        numberOfMonths: 1,
        buttonImageOnly: true,
        changeYear: true,
        showButtonPanel: true,
        onSelect: function( selectedDate ) {
            var option = this.id == "schoolkid_birthday",
            instance = $( this ).data( "datepicker" ),
            date = $.datepicker.parseDate(
                instance.settings.dateFormat ||
                    $.datepicker._defaults.dateFormat,
                selectedDate, instance.settings );
            dates.not( this ).datepicker( "option", option, date );
        }
    });
});

function remove_fields(link) {
    $(link).prev("input[type=hidden]").val("1");
    $(link).closest(".fields").hide();
}

function add_fields(link, association, content) {
    var new_id = new Date().getTime();
    var regexp = new RegExp("new_" + association, "g")
    $(link).parent().before(content.replace(regexp, new_id));
}

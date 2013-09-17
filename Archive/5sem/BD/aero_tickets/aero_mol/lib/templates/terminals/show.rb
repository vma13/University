"
<table class = 'list'>
  <caption>
    #{@header}<br>
    <span style = 'color: Red;'>#{@message}</span>
  </caption>
  <thead>
  <tbody>
    <tr>
      <th>Название посадочного терминала:</th>
      <td>#{@item[:name]}</td>
    </tr>
    <tr>
      <th>Описание:</th>
      <td>#{@item[:description]}</td>
    </tr>
    <tr>
      <th>Необходим автобус:</th>
      <td>#{@item[:needs_bus] ? "Да" : "Нет"}</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th colspan = '2'>
        <input type = 'button' value = 'Назад к списку'
               onclick = 'javascript:document.location=\"aero.rb?controller=Terminals&action=list\"'>
      </th>
    </tr>
  </tfoot>
</table>
"

count = 0
"
<table class = 'list'>
  <caption>
    #{create_link(@controller) if @user}
  </caption>
  <thead>
    <tr>
      <th>
        Название посадочного терминала
      </th>
      <th>
        Описание
      </th>
      <th>
        Необходим автобус
      </th>
      <th>
        Действия
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count%2}'>
      <td>#{i[:name]}</td>
      <td>#{i[:description]}</td>
      <td>#{i[:needs_bus] ? "Да" : "Нет"}</td>
      <td>
        #{view_link(@controller, i[:id])}
        #{edit_link(@controller, i[:id]) if @user}
        #{destroy_link(@controller, i[:id]) if @user}
      </td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"

count = 0
"
<table class = 'list'>
  <caption>
    #{create_link(@controller) if @user}
  </caption>
  <thead>
    <tr>
      <th>
        Название регистрационной стойки
      </th>
      <th>
        Описание
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
      <td>
        #{action_links(@controller, i[:id], @user)}
      </td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"

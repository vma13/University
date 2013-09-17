count = 0
"
<table class = 'list'>
  <caption>
    #{create_link(@controller) if @user && @action == :list}
  </caption>
  <thead>
    <tr>
      <th>
        Название авиакомпании
      </th>
      <th>
        Код
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
      <td>#{i[:code]}</td>
      <td>#{i[:description]}</td>
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

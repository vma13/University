count = 0
"
<table class = 'list'>
  <caption>
    <a href = 'aero.rb?controller=#{@controller}&action=edit'>Создать новую запись</a>
  </caption>
  <thead>
    <tr>
      <th>
       № Самолета
      </th>
      <th>
        Марка
      </th>
      <th>
        Компания
      </th>
      <th>
        Возраст
      </th>
      <th>
        Общая стоимость проведенных работ
      </th>
      <th>
        Статус
      </th>
    </tr>
  </thead>
  <tbody>
" + @items.map do |i|
      count += 1
"
    <tr class = 'list#{count % 2}'>
      <td>#{i[:id]}</td>
      <td>#{i[:mark]}</td>
      <td>#{i[:i.company_id()}</td>
      <td>#{i[:age]}</td>
      <td>#{i[:status]}</td>
      <td>#{i[:all_price]}</td>
      <td>
        <a href = 'aero.rb?controller=#{@controller}&action=edit&id=#{i[:id]}'>Редактировать</a>
        <a href = 'aero.rb?controller=#{@controller}&action=destroy&id=#{i[:id]}'>Удалить</a>
      </td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"

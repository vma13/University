count = 0
"
<table class = 'list'>
  <caption>
    #{@header}
  </caption>
  <thead>
    <tr>
      <th>
        №Самолета
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
      <td>#{i.company_id()}</td>
      <td>#{i[:age]}</td>
      <td>#{i[:all_price]}</td>
      <td>#{i[:status]}</td>
    </tr>
"
end.join("\n") + "
  </tbody>
</table>
"

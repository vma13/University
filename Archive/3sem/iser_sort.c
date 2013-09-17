for (i = 0; i < size - 1; i++) {
/* устанавливаем начальное значение минимального индекса */
        min_i = i;
	/* находим минимальный индекс элемента */
	for (j = i + 1; j < size; j++) {
		if (array[j] < array[min_i]) {
			min_i = j;
		}
	}
	/* меняем значения местами */
	temp = array[i];
	array[i] = array[min_i];
	array[min_i] = temp;
}


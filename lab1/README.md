# Лабораторная работа 1 (Задача 1)
## Hello World с OpenMP

### Сборка
```bash
gcc zadanie_1.cpp -o zadanie_1 -fopenmp
```

### Запуск
```bash
zadanie_1.exe
```

### Пример:
```bash
zadanie_1.exe
```

### Где:
- Программа запрашивает число потоков N с клавиатуры
- Каждый поток выводит `Thread <tid> of <nthreads>: Hello World`

---

# Лабораторная работа 1 (Задача 2)
## Сглаживание массива

### Сборка
```bash
gcc zadanie_2.cpp -o zadanie_2 -fopenmp
```

### Запуск
```bash
zadanie_2.exe
```

### Пример:
```bash
zadanie_2.exe
```

### Где:
- Программа запрашивает число потоков с клавиатуры
- Массив `a[N]` (N = 16000) инициализируется значениями `a[i] = i`
- Массив `b[N]` вычисляется как среднее соседних элементов: `b[i] = (a[i-1] + a[i] + a[i+1]) / 3.0`
- Сравниваются стратегии: `static`, `dynamic, 100`, `guided, 100`, `runtime`

---

# Лабораторная работа 1 (Задача 3)
## Упорядоченный вывод потоков (5 способов синхронизации)

### Сборка
```bash
gcc zadanie_3_1.cpp -o zadanie_3_1 -fopenmp
gcc zadanie_3_2.cpp -o zadanie_3_2 -fopenmp
gcc zadanie_3_3.cpp -o zadanie_3_3 -fopenmp
gcc zadanie_3_4.cpp -o zadanie_3_4 -fopenmp
gcc zadanie_3_5.cpp -o zadanie_3_5 -fopenmp
```

### Запуск
```bash
zadanie_3_1.exe
zadanie_3_2.exe
zadanie_3_3.exe
zadanie_3_4.exe
zadanie_3_5.exe
```

### Пример:
```bash
zadanie_3_1.exe
```

### Где:
- Программа запрашивает число потоков с клавиатуры
- Каждый поток по очереди (в порядке убывания номера) выводит `Potok <tid>: Hello World`

### Способы синхронизации:

| № | Файл | Способ |
|---|------|--------|
| 1 | `zadanie_3_1.cpp` | `#pragma omp atomic` — атомарное уменьшение счётчика |
| 2 | `zadanie_3_2.cpp` | `#pragma omp critical` — критическая секция |
| 3 | `zadanie_3_3.cpp` | `#pragma omp barrier` — барьер на каждой итерации |
| 4 | `zadanie_3_4.cpp` | `omp_lock_t` — блокировка через OpenMP-лок |
| 5 | `zadanie_3_5.cpp` | `#pragma omp single` — один поток печатает за всех |

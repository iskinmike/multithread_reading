# multithread_reading
Чтение и парсинг json файлов в несколько потоков с использованием rapidjson.

rapidjson добавлен как подмодуль. Для его инициализации, после клонирования репозитория, необходимо перейти в каталог rapidjson и выполнить команды:

```bash
	$ git submodule init
	$ git submodule update
```

Результат работы программы сохраняется в файл agr.txt


### Пример тестового файла

```json
{"ts_fact" : 1489494303, "fact_name": "fact1", "actor_id": 111222, "props": {"prop1": 11, "prop2": 22, "prop3": 33, "prop4": 44, "prop5": 55, "prop6": 66, "prop7": 77, "prop8": 88, "prop9": 99,"prop10": 1010}}
{"ts_fact" : 1489494303, "fact_name": "fact2", "actor_id": 111222, "props": {"prop1": 11, "prop2": 22, "prop3": 33, "prop4": 44, "prop5": 55, "prop6": 66, "prop7": 77, "prop8": 88, "prop9": 99,"prop10": 1010}}
{"ts_fact" : 1489494303, "fact_name": "fact3", "actor_id": 111222, "props": {"prop1": 11, "prop2": 22, "prop3": 33, "prop4": 44, "prop5": 55, "prop6": 66, "prop7": 77, "prop8": 88, "prop9": 99,"prop10": 1010}}
{"ts_fact" : 1489494303, "fact_name": "fact4", "actor_id": 111222, "props": {"prop1": 11, "prop2": 22, "prop3": 33, "prop4": 44, "prop5": 55, "prop6": 66, "prop7": 77, "prop8": 88, "prop9": 99,"prop10": 1010}}
```
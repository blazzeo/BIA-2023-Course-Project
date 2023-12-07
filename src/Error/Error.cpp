#include "Error.h"
#include "iostream"

namespace Error {
  ERROR errors[ERROR_MAX_ENTRY] = {
  // 0-99 Системные
    ERROR_ENTRY(0, "Недопустимый код ошибки"),
    ERROR_ENTRY(1, "Системный сбой"),
    ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
    ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
  //  100-199 Ошибки праметров
    ERROR_ENTRY(100, "Параметр -in должен быть задан"),
    ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
    ERROR_ENTRY(104, "Превышена длина входного пармаетра"),
    ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
    ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
    ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
    ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
    ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
    ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
  //  200-299 Ошибки лексического анализа
  ERROR_ENTRY(201, "Цепочка не разобрана"),
  ERROR_ENTRY(202, "Ошибка при создании файла IT"),
  ERROR_ENTRY(203, "Ошибка при создании файла LT"),
  ERROR_ENTRY(204, "Ошибка при получении строки лексической таблицы (нет элемента)"),
  ERROR_ENTRY(205, "Ошибка при получении строки таблицы идентификаторов (нет элемента)"),
  ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
  ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
  ERROR_ENTRY_NODEF100(300),
  //  400-499 Ошибки семантичского анализа
  ERROR_ENTRY(400, "Невозможно применить оператор к данному типу операнда"), ERROR_ENTRY(401, "Тип возвращаемого значения не соответствует типу функции"), ERROR_ENTRY(402, "Использована необъявленная переменная"), ERROR_ENTRY(403, "Повторное объявление имени"), ERROR_ENTRY(404, "Функция должна возвращать значение"), ERROR_ENTRY(405, "Ошибка в условии условного оператора"), ERROR_ENTRY(406, "Несовпадение фактических и формальных параметров функции"), ERROR_ENTRY(407, "Несоответсвие типов в выражении"), ERROR_ENTRY_NODEF(408), ERROR_ENTRY_NODEF(409), ERROR_ENTRY_NODEF10(410), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF10(450), ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480), ERROR_ENTRY_NODEF10(490),
  ERROR_ENTRY_NODEF100(500),
  //  600-699 Ошибки синтаксического анализа
  ERROR_ENTRY(600, "Неверная структура программы"),ERROR_ENTRY(601, "Ошибочный оператор"),ERROR_ENTRY(602, "Ошибка в выражении"),ERROR_ENTRY(603, "Ошибка в операторах функции"),ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),ERROR_ENTRY(605,"Значением данного оператора может быть только переменная или литерал"),ERROR_ENTRY(606,"Ошибка в условии условного оператора"),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
  ERROR_ENTRY_NODEF100(700),
  ERROR_ENTRY_NODEF100(800),
  ERROR_ENTRY_NODEF100(900)
  };

ERROR geterror(int id) {
  return id > 0 && id < ERROR_MAX_ENTRY ? errors[id] : errors[0];
}

ERROR geterrorin(int id, int line = -1, int col = -1) {
  ERROR err = geterror(id);
  err.inext.line = (short)line;
  err.inext.col = (short)col;
  return err;
}

ERROR geterrorlexer(int id, int line, std::string error_word) {
    ERROR err = geterrorin(id, line);
    std::cout << "Word : " << error_word << std::endl;
    err.error_line = error_word;
    return err;
}

};

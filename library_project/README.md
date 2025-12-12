Чтобы собрать и запустить это консольное приложение:
1)Выгрузите себе все файлы
2)В visual studio code откройте паапку library_project, настройте окружение и в настройках терминала установите Select Default Profile как Git Bash
3)Открой терминал: "Crtl" + "~", и выполните следущие комманды:
    mkdir build
    cd build
    cmake ..
    cmake --build .
4) После этого в build -> Debug появится library.exe, запускаем. Готово!

(Чтобы символы русского алфавита отображались корректно, в редакторе кода измените кодировку на windows 1251, для этого в visual studio code нажмите на кодировку -> Reopen with Encoding -> Windows 1251 или Cyrrilic Windows 1251)

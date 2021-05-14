TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    src/LL1_parser/construct_grammar.cpp \
    src/LL1_parser/eliminate_left_recursion.cpp \
    src/LL1_parser/eliminate_left_factoring.cpp \
    src/LL1_parser/ll1_grammar.cpp \
    src/LL1_parser/parsing.cpp \
    src/Lexical/c_lexical.cpp \
    src/slr1_parser/slr_parser.cpp \
    src/Grammar/grammar.cpp \
    src/Grammar/find_first.cpp \
    src/Grammar/find_follow.cpp \
    src/slr1_parser/slr_string_parsing.cpp \
    src/clr1_parser/clr_parser.cpp \
    src/clr1_parser/clr_string_parsing.cpp \
    src/Parser/parser.cpp \
    src/test/ue163062.cpp


HEADERS += \
    header/ll1parser.h \
    header/lexical_header.h \
    header/slr1_parser.h \
    header/grammar.h \
    header/project_header.h \
    header/clr1_parser.h \
    header/parser_header.h \
    header/ue163062.h

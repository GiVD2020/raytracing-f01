#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string>

using namespace std;

/*
Lectura d'un fitxer OBJ

Fragments de codi de obj_2_ply.c (C) Greg Turk

-----------------------------------------------------------------------
Copyright (c) 1998 Georgia Institute of Technology.  All rights reserved.

Permission to use, copy, modify and distribute this software and its
documentation for any purpose is hereby granted without fee, provided
that the above copyright notice and this permission notice appear in
all copies of this software and that you do not sell the software.
*/

class ReadObj
{
public:

    static int max_words;
    static int num_words;
    /* for file reading */
    #define BIG_STRING 4096
    static char str[BIG_STRING];
    static char str_orig[BIG_STRING];
    static char**words;

    static void get_indices ( char *word, int *vindex, int *tindex, int *nindex );
    static char *fetch_line ( FILE *fp );
    static int fetch_words ();
    static std::string getPath(const std::string& filename);

};


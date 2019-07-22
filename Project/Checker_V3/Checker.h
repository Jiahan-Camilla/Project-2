/*
 * File:   checker.h
 * Author: Jiahan Chen
 * Created on 7/22/2019
 * Purpose:  Checker Implementation
 */
 
#pragma once
#include <iostream> //I/O Library
#include <fstream>  //File I/O
#include <iomanip>  //Format Library
#include <cstdlib>  //Rand/Srand
#include <ctime>    //Time
#include <string>  //String
#include <cmath>   //Math

#define SIZE 8

using namespace std;

enum class piece : short
{
	EMPTY = 1, RED, WHITE, REDKING, WHITEKING
};

void swap(int&, int&);
bool CheckWin(int* state);
void DisplayBoard(int* state, char* symbol);
bool PlayerTurn(int* state, int, int*);
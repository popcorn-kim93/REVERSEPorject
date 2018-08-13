// Fill out your copyright notice in the Description page of Project Settings.

#include "C_ReverseGI.h"


UC_ReverseGI::UC_ReverseGI() {
	DoReverse = false;
}

void UC_ReverseGI::ReverseActivate() {
	DoReverse = true;
}

void UC_ReverseGI::ReverseDeActivate() {
	DoReverse = false;
}

bool UC_ReverseGI::GetReverseStatus() {
	return DoReverse;
}
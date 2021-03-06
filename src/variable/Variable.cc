/**
 * @file	Variable.cc
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.99
 * @date	2015 jun 01
 */


#include "Variable.h"

#include <omnetpp.h>
#include <stdlib.h>

// TODO check NONE type in all the methods

Variable :: Variable(){

	value = "";
	type = variable_t::NONE;
	
}


Variable :: Variable(const string value, const variable_t type){
	
	this->value = value;
	this->type = type;

}


Variable :: Variable(const Variable& obj){
	
	this->value = obj.value;
	this->type = obj.type;

}


Variable :: ~Variable(){

}


Variable Variable :: operator+(const Variable& obj) const{
	
	string rValue;
	variable_t rType;

	if(type != obj.type){
		opp_error("Variable::operator+ type mismatch");
	}
	
	switch(type){

		case variable_t::NUMBER:{
			
			rValue = to_string(double(*this) + double(obj));
			rType = variable_t::NUMBER;
			break;
		
		}
		
		case variable_t::STRING:{	
		
			// TODO check if they have a NUMBER format?
			rValue =  value + obj.value;
			rType = variable_t::STRING;
			break;
		
		}
		
		case variable_t::NONE:{
		
			opp_error("Variable::operator+ does not support NONE type type ");
		
		}
		
	}	
	
	return Variable(rValue, rType);

}


Variable Variable :: operator+(const int number) const {
	
	string rValue;

	if(type != variable_t::NUMBER){
		opp_error("Variable::operator+ type mismatch, it supports only NUMBER type");
	}

	rValue = to_string(double(*this) + (double)number);

	return Variable(rValue, variable_t::NUMBER);

}


Variable& Variable :: operator++(){
	
	switch(type){

		case variable_t::NUMBER:{ 
			*this = *this + 1 ;
			break;
		}
			
		default:{ 	
			opp_error("Variable::operator++ supports only NUMBER type, doesn't support STRING or NONE types");
		}
		
	}	
	
	return *this;

}


Variable& Variable :: operator++(int){

	// invoke the prefix operator
	return ++(*this);

}


Variable Variable :: operator-(const Variable& obj) const{
	
	string rValue;
	variable_t rType;

	if(type != obj.type){
		opp_error("Variable::operator- type mismatch");
	}
	
	switch(type){

		case variable_t::NUMBER:{
			
			rValue = to_string(double(*this) - double(obj));
			rType = variable_t::NUMBER;
			break;
			
		}
			
		default:{
			
			opp_error("Variable::operator- supports only NUMBER type");
			
		}

	}	
	
	return Variable(rValue, rType);

}


Variable& Variable :: operator--(){

	switch(type){

		case variable_t::NUMBER:{
		
			value = to_string( double(*this) - 1 );
			break;
		
		}

		default:{
		
			opp_error("Variable::operator-- supports only NUMBER type");
		
		}
		
	}

	return *this;

}


Variable& Variable :: operator--(int){

	return --(*this);

}


Variable Variable :: operator*(const Variable& obj) const{

	string rValue;

	if(type != obj.type){
		opp_error("Variable::operator* type mismatch");
	}
	
	switch(type){

		case variable_t::NUMBER:{
		
			rValue = to_string( double(*this) * double(obj) );
			break;
		
		}
			
		default:{

			opp_error("Variable::operator* supports only NUMBER type");
			break;
		
		}

	}	
	
	return Variable(rValue, variable_t::NUMBER);
	
}


Variable Variable :: operator/(const Variable& obj) const{

	string rValue;

	if(type != obj.type ){
		opp_error("Variable::operator/ type mismatch");
	}
		
	switch(type){

		case variable_t::NUMBER:{

			if(double(obj) == 0){
			  opp_error("Variable::operator/ zero division error");
			}
				
			rValue = to_string( double(*this) / double(obj) );
			break;
			
		}
		
		default:{
		
			opp_error("Variable::operator/ supports only NUMBER type");

		}

	}
	
	return Variable(rValue, variable_t::NUMBER);
	
}


Variable Variable :: operator%(const Variable& obj) const{

	string rValue;

	if(type != obj.type){
		opp_error("Variable::operator% type mismatch");
	}
	
	switch(type){

		case variable_t::NUMBER:{
		
			rValue = to_string( int(*this) % int(obj) );
			break;
		
		}
			
		default:{

			opp_error("Variable::operator% supports only NUMBER type");
		
		}

	}	
	
	return Variable(rValue, variable_t::NUMBER);
	
}



Variable& Variable :: operator=(const Variable& obj){

	value = obj.value;
	type = obj.type;

	return *this;

}


Variable& Variable :: operator+=(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator+= type mismatch");
	}

	switch(type){

		case variable_t::NUMBER:{
		
			*this = *this + obj;
			break;
		
		}
			
		case variable_t::STRING:{

			value = value + obj.value;
			break;
		
		}
		
		case variable_t::NONE:{
		
			opp_error("Variable::operator+= does not support NONE type");
		
		}
		

	}	
	
	return *this;
	
}


Variable& Variable :: operator-=(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator-= type mismatch");
	}

	switch(type){

		case variable_t::NUMBER:{
		
			value = to_string( double(*this) - double(obj) );
			break;
		
		}
			
		default:{ 	
		
			opp_error("Variable::operator-= does not support STRING type");
		
		}

	}	
	
	return *this;
	
}


Variable& Variable :: operator*=(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator*= type mismatch");
	}

	switch(type){

		case variable_t::NUMBER:{
		
			*this = *this * obj;
			break;
		
		}
			
		default:{

			opp_error("Variable::opeartor*= does not support STRING type");

		}

	}	
	
	return *this;

}


Variable& Variable :: operator/=(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator/= type mismatch");
	}

	switch(type){

		case variable_t::NUMBER:{ 
		
			*this = *this / obj;
			break;
		
		}
			
		default:{

			opp_error("Variable::operator/= does not support STRING type");

		}

	}	
	
	return *this;
	
}


Variable& Variable :: operator%=(const Variable& obj){
	
	if(type != obj.type){
		opp_error("Variable::operator%= type mismatch");
	}

	switch(type){

		case variable_t::NUMBER:{

			*this = *this % obj;
			break;

		}
			
		default:{
		
			opp_error("Variable::operator%= does not support STRING type");
		
		}

	}	
	
	return *this;
}


Variable Variable :: cast_int() const{
	
	string rValue;	

	switch(type){

		case variable_t::NUMBER:{
		 	
		 	rValue = to_string( int(*this) );
			break;
		
		}
	
		case variable_t::STRING:{

			if( get_variable_format(value) != variable_t::NUMBER ){
				opp_error("Variable::cast_int supports only NUMBER type or STRING type having NUMBER format");
			}

		}
		
		case variable_t::NONE:{
		
			opp_error("Variable::cast_int doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
		
		}		

	}	
	
	return Variable(rValue, variable_t::NUMBER);

}


Variable Variable :: cast_double() const{
	
	string rValue;	

	switch(type){

		case variable_t::NUMBER:{
		 	
		 	rValue = to_string( double(*this) );
			break;

		}

		case variable_t::STRING:{
		
			if( get_variable_format(value) != variable_t::NUMBER ){
				opp_error("Variable::cast_double supports only NUMBER type or STRING type having NUMBER format");
			}

		}

		case variable_t::NONE:{
		
			opp_error("Variable::cast_double doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
		
		}

	}	
	
	return Variable(rValue, variable_t::NUMBER);
	
}


Variable :: operator bool() {
	
	int rValue;

	switch(type){

		case variable_t::NUMBER:{
			rValue = atoi( value.c_str() );
			break;
		}

		case variable_t::STRING:{
		
			if(get_variable_format(value) != variable_t::NUMBER){
				opp_error("Variable::operator bool() supports only NUMBER type or STRING type with NUMBER format");
			}
		
		}
				
		case variable_t::NONE:{
		
			opp_error("Variable::bool doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
		
		}	

	}	
	
	if( rValue ){
		return true;
	}
	else{
		return false;
	}
	
}


Variable :: operator int(){
	
	int rValue;	

	switch(type){

		case variable_t::NUMBER:{
		
		 	rValue = atoi( value.c_str() );
			break;
		
		}
		
		case variable_t::STRING:{
		
			if( get_variable_format(value) != variable_t::NUMBER){
				opp_error("Variable::operator int() supports only NUMBER type or STRING type with NUMBER format");
			}
		
		}

		case variable_t::NONE:{
		
			opp_error("Variable::int doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
		
		}

	}	
	
	return rValue;
	
}


Variable :: operator int() const{

	int rValue;	

	switch(type){

		case variable_t::NUMBER:{
		
		 	rValue = atoi( value.c_str() );
			break;
			
		}
		
		case variable_t::STRING:{ 	

			if(get_variable_format(value) != variable_t::NUMBER){
				opp_error("Variable::operator int() supports only NUMBER type or STRING type with NUMBER format");
			}
			
		}				

		case variable_t::NONE:{
		
		 	opp_error("Variable::int const doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
			
		}

	}	
	
	return rValue;
	
}


Variable :: operator double(){
	
	double rValue;	

	switch(type){

		case variable_t::NUMBER:{
		 
		 	rValue = atof( value.c_str() );
			break;
		
		}
		
		case variable_t::STRING:{
		
			if(get_variable_format(value) != variable_t::NUMBER){
				opp_error("Variable::operator double() supports only NUMBER type or STRING type with NUMBER format");
			}
		
		}
		
		case variable_t::NONE:{
		
		 	opp_error("Variable::double doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
			
		}

	}	
	
	return rValue;
	
}


Variable :: operator double() const{
	
	double rValue;	

	switch(type){

		case variable_t::NUMBER:{
		
		 	rValue = atof( value.c_str() );
			break;
		}

		case variable_t::STRING:{
		
			if(get_variable_format(value) != variable_t::NUMBER){
				opp_error("Variable::operator double() supports only NUMBER type or STRING type with NUMBER format");
			}
		
		}

		case variable_t::NONE:{
		
		 	opp_error("Variable::double const doesn't support NONE type, it supports only NUMBER type or STRING type having NUMBER format ");
			
		}		
				
	}	
	
	return rValue;
	
}


Variable Variable :: operator==(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator== type mismatch");
	}

	switch(type){	

		case variable_t::STRING:{
			
			if ( value == obj.value ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
			
		}
			
		case variable_t::NUMBER:{
			
			if ( double(*this) == double(obj) ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
				
		}
		
		case variable_t::NONE:{
		
		 	opp_error("Variable::opeartor== doesn't support NONE type");
			
		}
			
	}

}


Variable Variable :: operator!=(const Variable& obj){

	if ( !(*this == obj) ){
		return Variable("1", variable_t::NUMBER);
	}
	else{
		return Variable("0", variable_t::NUMBER);
	}
	
}


Variable Variable :: operator>=(const Variable& obj){

	if ( (*this == obj) || (*this > obj)){
		return Variable("1", variable_t::NUMBER);
	}
	else{
		return Variable("0", variable_t::NUMBER);
	}

}


Variable Variable :: operator<=(const Variable& obj){

	if ( (*this == obj) || (*this < obj) ){
		return Variable("1", variable_t::NUMBER);
	}
	else{
		return Variable("0", variable_t::NUMBER);
	}
	
}


Variable Variable :: operator>(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::operator> type mismatch");
	}

	switch(type){	

		case variable_t::NUMBER:{
			
			if ( double(*this) > double(obj) ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
			
		}

		case variable_t::STRING:{
			
			if ( atof(value.c_str()) > atof((obj.value).c_str()) ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
			
		}
		
		case variable_t::NONE:{
		
		 	opp_error("Variable::opeartor> doesn't support NONE type");
			
		}


	}

}


Variable Variable :: operator<(const Variable& obj){

	if(type != obj.type){
		opp_error("Variable::opeartor< type mismatch");
	}

	switch(type){	

		case variable_t::NUMBER:{
		
			if ( double(*this) < double(obj) ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
		
		}

		case variable_t::STRING:{
		
			if ( atof(value.c_str()) < atof((obj.value).c_str()) ){
				return Variable("1", variable_t::NUMBER);
			}
			else{
				return Variable("0", variable_t::NUMBER);
			}
		
		}	
		
		case variable_t::NONE:{
		
		 	opp_error("Variable::opeartor< doesn't support NONE type");
			
		}
		
	}

}


Variable Variable :: operator&&(const Variable& obj){

	if ( int(*this) && int(obj) ){
		return Variable("1", variable_t::NUMBER);
	}
	else{
		return Variable("0", variable_t::NUMBER);
	}

}


Variable Variable :: operator||(const Variable& obj){

	if ( int(*this) || int(obj) ){
		return Variable("1", variable_t::NUMBER);
	}
	else{
		return Variable("0", variable_t::NUMBER);
	}

}


Variable Variable::operator!(){

	if ( int(*this) ){
		return Variable("0", variable_t::NUMBER);
	}
	else{
		return Variable("1", variable_t::NUMBER);
	}

}


string Variable :: getValue() const{

	return value;

}


variable_t Variable :: getType() const{

	return type;

}


ostream& operator<<(ostream& os, Variable& obj){

	os << obj.getValue();
  
	return os;
	
}


variable_t get_variable_format(string value){
	
	char* p;
	strtod( value.c_str(), &p );
	
	if ( *p == 0.0 ){
	   return variable_t::NUMBER;
	}
	else{
		return variable_t::STRING;
	}

}


string to_string(const variable_t type){

	switch(type){
	
		case variable_t::STRING:{		
			return "STRING";
		}

		case variable_t::NUMBER:{		
			return "NUMBER";
		}

		case variable_t::NONE:{		
			return "NONE";
		}
	
	}
	
	opp_error("Function to_string (from variable_t to string) doesn't recognize the argument");

}


variable_t to_variable_t(const string type){
	
	if(type == "STRING"){
		return variable_t::STRING;
	}
	else{
	
		if(type == "NUMBER"){
			return variable_t::NUMBER;
		}
		else{

			if(type == "NONE"){
				return variable_t::NONE;
			}
			else{
				opp_error("Function to_variable_t (from string to variable_t) doesn't recognize the argument");
			}
		
		}
	
	}

}


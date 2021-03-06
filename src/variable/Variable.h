/**
 * @file	Variable.h
 * @author	Francesco Racciatti <racciatti.francesco@gmail.com>
 * @version	0.99
 * @date	2015 jun 01
 *
 * @brief	This class implements Variable objects.
 *
 * @details	A Variable object includes the following two fields:
 *			 - value,
 *			 - type (i.e. either NUMBER, STRING or NONE)
 *
 */


#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <cstdint>
#include <string>


using namespace std;


/**
 * @brief 	Type of the variable
 * @detail 	A Variable can assume one of three types:
 *			 - STRING
 *			 - NUMBER
 *			 - NONE
 */
enum class variable_t : uint8_t{
	NUMBER = 0,
	STRING,
	NONE
};


class Variable{

	string value;
	variable_t type;

	public:

		Variable();
		Variable(const string value, const variable_t type);
		Variable(const Variable& obj);
		
		~Variable();

		Variable operator+(const Variable& obj) const;
		Variable operator+(const int number) const;
		Variable& operator++();
		Variable& operator++(int);

		Variable operator-(const Variable& obj) const;
		Variable& operator--();
		Variable& operator--(int);

		Variable operator*(const Variable& obj) const;
		Variable operator/(const Variable& obj) const;
		Variable operator%(const Variable& obj) const;

		Variable& operator=(const Variable& obj);
		Variable& operator+=(const Variable& obj);
		Variable& operator-=(const Variable& obj);
		Variable& operator*=(const Variable& obj);
		Variable& operator/=(const Variable& obj);
		Variable& operator%=(const Variable& obj);

		Variable cast_int() const;
		Variable cast_double() const;

		operator bool();
		operator int();
		operator int() const;
		operator double();		
		operator double() const;

		Variable operator==(const Variable& obj);
		Variable operator!=(const Variable& obj);
		Variable operator>=(const Variable& obj);
		Variable operator<=(const Variable& obj);
		Variable operator>(const Variable& obj);
		Variable operator<(const Variable& obj);

		Variable operator&&(const Variable& obj);
		Variable operator||(const Variable& obj);
		Variable operator!();
	
		string getValue() const;
		variable_t getType() const;
	
		friend ostream& operator<<(ostream& os, Variable& obj);
	
};

/**
 * @brief 	Return the format of the variable
 * @detail	Return the format of the variable:
 *			 - a NUMBER Variable has a NUMBER format
 *			 - a STRING Variable could have a NUMBER format
 */
variable_t get_variable_format(string value);

/**
 * @brief Convert a string in a variable_t type if possible
 */ 
string to_string(const variable_t type);

/**
 * @brief Convert a variable_t type in a string if possible
 */
variable_t to_variable_t(const string type);

#endif

/*
 * LibAnvil
 * Copyright (C) 2012 - 2020 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "../../include/byte_stream.h"
#include "../../include/tag/double_tag.h"

/*
 * Double tag assignment operator
 */
double_tag &double_tag::operator=(const double_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	name = other.name;
	type = other.type;
	value = other.value;
	return *this;
}

/*
 * Double tag equals operator
 */
bool double_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const double_tag *other_tag = dynamic_cast<const double_tag *>(&other);
	if(!other_tag)
		return false;

	// check attributes
	return name == other.name
			&& type == other.type
			&& value == other_tag->value;
}

/*
 * Return a double tag's data
 */
std::vector<char> double_tag::get_data(bool list_ele)  {
	byte_stream stream(byte_stream::SWAP_ENDIAN);

	// form data representation
	if(!list_ele) {
		stream << (char) type;
		stream << (short) name.size();
		stream << name;
	}
	stream << value;
	return stream.vbuf();
}

/*
 * Return a string representation of a double tag
 */
std::string double_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form string representation
	ss << generic_tag::to_string(tab) << ": " << value;
	return ss.str();
}

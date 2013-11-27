/*
 * fimex/metlibs, deprecated.h
 *
 * (C) Copyright 2013, met.no
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 *  Created on: Apr 28, 2010
 *      Author: Heiko Klein
 */

#ifndef METLIBS_DEPRECATED_H_
#define METLIBS_DEPRECATED_H_
#define METLIBS_SUPPRESS_DEPRECATED
#define METLIBS_CONCAT(...) __VA_ARGS__
#if defined(METLIBS_SUPPRESS_DEPRECATED)
#define METLIBS_DEPRECATED(func, message) func
#elif defined(__GNUC__) or defined(__clang__)
#define METLIBS_DEPRECATED(func, message) func __attribute__ ((deprecated(message)))
#elif defined(_MSC_VER)
#define METLIBS_DEPRECATED(func, message) __declspec(deprecated) func
#elif defined(__IBMC__) || defined(__IBMCPP__)
/* "METLIBS_DEPRECATED not implemented for IBM compilers" */
#define METLIBS_DEPRECATED(func, message) func
#else
#pragma message("WARNING: You need to implement METLIBS_DEPRECATED for this compiler")
#define METLIBS_DEPRECATED(func, message) func
#endif

#endif /* METLIBS_DEPRECATED_H_ */

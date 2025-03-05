/* Copyright 2023 Cheng Liren
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#define LOG_LEVEL_NONE    0
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4

#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#define LOG(level, format, ...)                                 \
    do {                                                        \
        if (level <= CURRENT_LOG_LEVEL) {                       \
            switch (level) {                                    \
                case LOG_LEVEL_ERROR:                           \
                    printf("[ERROR] " format, ##__VA_ARGS__);   \
                    break;                                      \
                case LOG_LEVEL_WARNING:                         \
                    printf("[WARNING] " format, ##__VA_ARGS__); \
                    break;                                      \
                case LOG_LEVEL_INFO:                            \
                    printf("[INFO] " format, ##__VA_ARGS__);    \
                    break;                                      \
                case LOG_LEVEL_DEBUG:                           \
                    printf("[DEBUG] " format, ##__VA_ARGS__);   \
                    break;                                      \
                default:                                        \
                    break;                                      \
            }                                                   \
        }                                                       \
    } while (0)

#define LOG_ERROR(format, ...)   LOG(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) LOG(LOG_LEVEL_WARNING, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)    LOG(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)   LOG(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_RAW                  printf
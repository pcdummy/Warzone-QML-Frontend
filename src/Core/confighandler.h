/*
	This file is part of Warzone 2100.
	Copyright (C) 2011  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
/**
 * @file configuration.h
 *
 * Configuration handlers.
 */
#ifndef __SRC_CORE_CONFIG_CONFIGHANDLER_H__
#define __SRC_CORE_CONFIG_CONFIGHANDLER_H__

#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtCore/QVariantMap>

enum CONFOPTION_TYPES
{
	CONFTYPE_ERROR,
	CONFTYPE_INT,
	CONFTYPE_BOOL,
	CONFTYPE_STRING,
	CONFTYPE_ENUM, // int bounds checked
	CONFTYPE_STRINGLIST
};

enum CONFIGCONTEXT
{
	CONFCONTEXT_USER,
	CONFCONTEXT_ENGINE
};

class ConfigHandlerPrivate;
class ConfigHandler : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor initializes defaults.
	 */
	ConfigHandler();

	/**
	 * @brief Destructor cleans this up especialy: m_userConfig and m_engineConfig.
	 */
	~ConfigHandler();

	/**
	 * @brief Reads and validates the users configuration.
	 *
	 * Reads the users ini configuration from the given path,
	 * e.g.: ~/.warzone2100-3.0/config
	 *
	 * And validates it.
	 *
	 * @param filename	  Users ini config path.
	 *
	 * @return Success/Failure.
	 */
	bool loadConfig(const QString &filename);

	/**
	 * @brief Stores the users configuration to the given path.
	 *
	 * @param filename	  Users ini config path.
	 * @param context	   Config context to store.
	 *
	 * @return Success/Failure.
	 */
	bool storeConfig(const QString& filename, CONFIGCONTEXT context = CONFCONTEXT_USER);

	/**
	 * @brief Registers a config value.
	 *
	 * @param key		   The key, must be unique.
	 * @param type		  Values type, one of CONFOPTION_TYPES.
	 * @param storeUserConf Store this value in the users configuration?
	 * @param defaultValue  Default, returned by get() if not overwritten by set().
	 * @param maxValue	  For CONFTYPE_ENUM the upper bound to allow.
	 *
	 * @return Success/Failure.
	 */
	bool add(const QString key, CONFOPTION_TYPES type, bool storeUserConf, QVariant defaultValue, qint32 maxValue = 0);

	/**
	 * @brief Sets a config value, does some type and bounds checking.
	 *
	 * @param key		   The key.
	 * @param value		 The value, will be checked for the type and bounds.
	 * @param store		 Store this value in the users configuration or just in the engines config?
	 *
	 * @return  Success/Failure.
	 */
	Q_INVOKABLE bool set(const QString key, QVariant value, bool store = true);

	Q_INVOKABLE QVariant get(const QString key);

private:
	ConfigHandlerPrivate* m_d;
};

// Global config holder.
extern ConfigHandler config;

#endif // #ifndef __SRC_CORE_CONFIG_CONFIGHANDLER_H__

/*
 * Copyright 2019 Aurélien Gâteau <mail@agateau.com>
 *
 * This file is part of Lovi.
 *
 * Lovi is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "highlight.h"

#include "conditionio.h"

Highlight::Highlight(LogFormat* logFormat) : mLogFormat(logFormat) {
    Q_ASSERT(mLogFormat);
}

void Highlight::setConditionDefinition(const QString& definition) {
    mConditionDefinition = definition;

    condition = ConditionIO::parse(definition, mLogFormat->columnHash());
    mLogFormat->emitHighlightChanged(this);
}

QString Highlight::conditionDefinition() const {
    return mConditionDefinition;
}

void Highlight::setScope(Highlight::Scope scope) {
    if (mScope == scope) {
        return;
    }
    mScope = scope;
    mLogFormat->emitHighlightChanged(this);
}

void Highlight::setBgColor(const OptionalColor& color) {
    mBgColor = color;
    mLogFormat->emitHighlightChanged(this);
}

void Highlight::setFgColor(const OptionalColor& color) {
    mFgColor = color;
    mLogFormat->emitHighlightChanged(this);
}

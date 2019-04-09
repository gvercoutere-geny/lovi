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
#ifndef LOGFORMATDIALOG_H
#define LOGFORMATDIALOG_H

#include <QDialog>
#include <QFileSystemModel>

#include <memory>

namespace Ui {
class LogFormatDialog;
}

class LogFormat;

class LogFormatModel : public QFileSystemModel {
    Q_OBJECT
public:
    LogFormatModel(QObject* parent = nullptr);
    ~LogFormatModel();

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    std::shared_ptr<LogFormat> logFormatForIndex(const QModelIndex& index) const;

private:
    QString nameForIndex(const QModelIndex& index) const;
};

class LogFormatDialog : public QDialog {
    Q_OBJECT
public:
    explicit LogFormatDialog(const QString& logFormatName, QWidget* parent = nullptr);
    ~LogFormatDialog();

    QString logFormatName() const;

signals:
    void logFormatChanged(const std::shared_ptr<LogFormat>& logFormat);

private:
    void setupSideBar();
    void setupEditor();

    void onCurrentChanged(const QModelIndex& index);
    void onRowsInserted(const QModelIndex& parent, int first, int last);
    void applyChanges();

    const std::unique_ptr<Ui::LogFormatDialog> ui;
    const std::unique_ptr<LogFormatModel> mModel;

    QString mInitialLogFormatPath;
};

#endif // LOGFORMATDIALOG_H

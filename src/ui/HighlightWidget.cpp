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
#include "HighlightWidget.h"

#include "ConditionLineEditChecker.h"
#include "LogFormat.h"
#include "ui_HighlightWidget.h"

using std::unique_ptr;

// Helper function to init `ui` and create all its widgets so that mLineEditChecker can be called
// with a valid QLineEdit instance
static unique_ptr<Ui::HighlightWidget> initUi(QWidget* parent) {
    auto ui = std::make_unique<Ui::HighlightWidget>();
    ui->setupUi(parent);
    return ui;
}

HighlightWidget::HighlightWidget(QWidget* parent)
        : QWidget(parent)
        , ui(initUi(this))
        , mLineEditChecker(std::make_unique<ConditionLineEditChecker>(ui->conditionLineEdit)) {
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setupUi();
}

HighlightWidget::~HighlightWidget() {
}

void HighlightWidget::setHighlight(Highlight* highlight) {
    if (mHighlight == highlight) {
        return;
    }
    mHighlight = highlight;
    if (!mHighlight) {
        setEnabled(false);
        return;
    }
    setEnabled(true);

    mLineEditChecker->setLogFormat(highlight->logFormat());
    ui->conditionLineEdit->setText(highlight->conditionDefinition());
    ui->bgColorWidget->setColor(highlight->bgColor());
    ui->fgColorWidget->setColor(highlight->fgColor());
    ui->scopeComboBox->setCurrentIndex(static_cast<int>(highlight->scope()));
}

Highlight* HighlightWidget::highlight() const {
    return mHighlight;
}

static void setLabelIcon(QLabel* label, const QString& name) {
    QIcon icon = QIcon::fromTheme(name);
    label->setPixmap(icon.pixmap(32));
    label->setFixedSize(label->pixmap()->size());
}

void HighlightWidget::setupUi() {
    setEnabled(false);
    layout()->setMargin(0);

    setLabelIcon(ui->bgColorLabel, "color-fill");
    setLabelIcon(ui->fgColorLabel, "format-text-color");

    connect(ui->conditionLineEdit, &QLineEdit::editingFinished, this, [this] {
        mHighlight->setConditionDefinition(ui->conditionLineEdit->text());
    });

    connect(ui->bgColorWidget,
            &ColorWidget::colorChanged,
            this,
            [this](const OptionalColor& color) { mHighlight->setBgColor(color); });

    connect(ui->fgColorWidget,
            &ColorWidget::colorChanged,
            this,
            [this](const OptionalColor& color) { mHighlight->setFgColor(color); });

    connect(ui->scopeComboBox, qOverload<int>(&QComboBox::activated), this, [this](int index) {
        auto scope = static_cast<Highlight::Scope>(index);
        mHighlight->setScope(scope);
    });
}

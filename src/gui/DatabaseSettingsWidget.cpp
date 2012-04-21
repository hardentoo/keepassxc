/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DatabaseSettingsWidget.h"
#include "ui_DatabaseSettingsWidget.h"


DatabaseSettingsWidget::DatabaseSettingsWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::DatabaseSettingsWidget())
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), SLOT(changeSettings()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));
}

DatabaseSettingsWidget::~DatabaseSettingsWidget()
{
}

void DatabaseSettingsWidget::setForms(QString dbName, QString dbDescription,
                                      bool recylceBinEnabled, int transformRounds)
{
    m_ui->dbNameEdit->setText(dbName);
    m_ui->dbDescriptionEdit->setText(dbDescription);
    if (recylceBinEnabled) {
        m_ui->recycleBinEnabledCheckBox->setCheckState(Qt::Checked);
    }
    else {
        m_ui->recycleBinEnabledCheckBox->setCheckState(Qt::Unchecked);
    }
    m_ui->transformRoundsSpinBox->setValue(transformRounds);
}

quint64 DatabaseSettingsWidget::transformRounds()
{
    return m_transformRounds;
}

QString DatabaseSettingsWidget::dbName()
{
    return m_dbName;
}

QString DatabaseSettingsWidget::dbDescription()
{
    return m_dbDescription;
}

bool DatabaseSettingsWidget::recylceBinEnabled()
{
    return m_recylceBinEnabled;
}

void DatabaseSettingsWidget::changeSettings()
{
    m_dbName = m_ui->dbNameEdit->text();
    m_dbDescription = m_ui->dbDescriptionEdit->text();
    if (m_ui->recycleBinEnabledCheckBox->checkState() == Qt::Checked) {
        m_recylceBinEnabled = true;
    }
    else {
        m_recylceBinEnabled = false;
    }
    m_transformRounds = m_ui->transformRoundsSpinBox->value();

    Q_EMIT editFinished(true);
}

void DatabaseSettingsWidget::reject()
{
    Q_EMIT editFinished(false);
}

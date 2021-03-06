/****************************************************************************
**
** Copyright (C) 2014 Alexander Rössler
** License: LGPL version 2.1
**
** This file is part of QtQuickVcp.
**
** All rights reserved. This program and the accompanying materials
** are made available under the terms of the GNU Lesser General Public License
** (LGPL) version 2.1 which accompanies this distribution, and is available at
** http://www.gnu.org/licenses/lgpl-2.1.html
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Lesser General Public License for more details.
**
** Contributors:
** Alexander Rössler @ The Cool Tool GmbH <mail DOT aroessler AT gmail DOT com>
**
****************************************************************************/
#ifndef QAPPDISCOVERYITEM_H
#define QAPPDISCOVERYITEM_H

#include <QObject>
#include <QHostAddress>
#include <QDateTime>

class QServiceDiscoveryItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString uri READ uri NOTIFY uriChanged)
    Q_PROPERTY(QString uuid READ uuid NOTIFY uuidChanged)
    Q_PROPERTY(int version READ version NOTIFY versionChanged)
    Q_PROPERTY(int port READ port NOTIFY portChanged)
    Q_PROPERTY(QHostAddress hostAddress READ hostAddress NOTIFY hostAddressChanged)
    Q_PROPERTY(QStringList txtRecords READ txtRecords NOTIFY txtRecordsChanged)
    Q_PROPERTY(bool updated READ updated WRITE setUpdated NOTIFY updatedChanged)

public:
    explicit QServiceDiscoveryItem(QObject *parent = 0);


    QString uri() const
    {
        return m_uri;
    }

    int port() const
    {
        return m_port;
    }

    QHostAddress hostAddress() const
    {
        return m_hostAddress;
    }

    QString name() const
    {
        return m_name;
    }

    QString type() const
    {
        return m_type;
    }

    QStringList txtRecords() const
    {
        return m_txtRecords;
    }

    QString uuid() const
    {
        return m_uuid;
    }

    int outstandingRequests() const
    {
        return m_outstandingRequests;
    }

    int version() const
    {
        return m_version;
    }

    bool updated() const
    {
        return m_updated;
    }

public slots:

    void setUri(QString arg)
    {
        if (m_uri != arg) {
            m_uri = arg;
            emit uriChanged(arg);
        }
    }
    void setPort(int arg)
    {
        if (m_port != arg) {
            m_port = arg;
            emit portChanged(arg);
        }
    }
    void setHostAddress(QHostAddress arg)
    {
        if (m_hostAddress != arg) {
            m_hostAddress = arg;
            emit hostAddressChanged(arg);
        }
    }

    void setName(QString arg)
    {
        if (m_name != arg) {
            m_name = arg;
            emit nameChanged(arg);
        }
    }

    void setType(QString arg)
    {
        if (m_type != arg) {
            m_type = arg;
            emit typeChanged(arg);
        }
    }

    void setTxtRecords(QStringList arg);

    void setUuid(QString arg)
    {
        if (m_uuid != arg) {
            m_uuid = arg;
            emit uuidChanged(arg);
        }
    }

    void setOutstandingRequests(int arg)
    {
        m_outstandingRequests = arg;
    }

    void setVersion(int arg)
    {
        if (m_version != arg) {
            m_version = arg;
            emit versionChanged(arg);
        }
    }

    void setUpdated(bool arg)
    {
        if (m_updated != arg) {
            m_updated = arg;
            emit updatedChanged(arg);
        }
    }

private:
    QString m_name;
    QString m_type;
    QString m_uri;
    QString m_uuid;
    int m_version;
    int m_port;
    QHostAddress m_hostAddress;
    QStringList m_txtRecords;
    int m_outstandingRequests;
    bool m_updated;

signals:
    void uriChanged(QString arg);
    void portChanged(int arg);
    void hostAddressChanged(QHostAddress arg);
    void nameChanged(QString arg);
    void typeChanged(QString arg);
    void txtRecordsChanged(QStringList arg);
    void uuidChanged(QString arg);
    void versionChanged(int arg);
    void updatedChanged(bool arg);
};

#endif // QAPPDISCOVERYITEM_H

/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include <QApplication>
#include <QWidget>
#include <QLabel>

#include "event_monitor.h"

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    QLabel *label = new QLabel("XRecord Example");
    
    QFont font;
    font.setPixelSize(30);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    
    EventMonitor eventMonitor;
    QObject::connect(
        &eventMonitor, 
        &EventMonitor::buttonPress, 
        label,
        [=] (int x, int y) {
            label->setText(QString("Button press (%1, %2)").arg(x).arg(y));
        }, 
        Qt::QueuedConnection);
    QObject::connect(
        &eventMonitor, 
        &EventMonitor::buttonDrag, 
        label,
        [=] (int x, int y) {
            label->setText(QString("Button drag (%1, %2)").arg(x).arg(y));
        }, 
        Qt::QueuedConnection);
    QObject::connect(
        &eventMonitor, 
        &EventMonitor::buttonRelease, 
        label,
        [=] (int x, int y) {
            label->setText(QString("Button release (%1, %2)").arg(x).arg(y));
        }, 
        Qt::QueuedConnection);
    QObject::connect(
        &eventMonitor, 
        &EventMonitor::keyPress, 
        label,
        [=] (int code) {
            label->setText(QString("Key press %1").arg(code));
        }, 
        Qt::QueuedConnection);
    QObject::connect(
        &eventMonitor, 
        &EventMonitor::keyRelease,
        label,
        [=] (int code) {
            label->setText(QString("Key release %1").arg(code));
        }, 
        Qt::QueuedConnection);
    eventMonitor.start();
    
    label->resize(440, 550);
    label->setWindowTitle("XRecord example");
    label->show();

    return app.exec();
}

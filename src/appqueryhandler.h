// Copyright (c) 2023 Manuel Schneider

#pragma once
#include "albert/extensions/queryhandler.h"

class AppQueryHandler : public albert::IndexQueryHandler
{
public:
    QString id() const override;
    QString name() const override;
    QString description() const override;
    void updateIndexItems() override;
};

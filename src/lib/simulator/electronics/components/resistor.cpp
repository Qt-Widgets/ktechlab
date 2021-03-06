/***************************************************************************
 *   Copyright (C) 2003 by David Saxton                                    *
 *   david@bluehaze.org                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "resistor.h"

#include "circuit.h"
#include "ecnode.h"
#include "variant.h"
#include <elementmap.h>
#include <resistance.h>

Resistor::Resistor(Circuit &ownerCircuit)
		: Component(ownerCircuit) {
    m_resistance = new Resistance();
    // FIXME: default value for resistance is 1 ohm, for resistor is 10k
    m_elemMap = new ElementMap(m_resistance);
    m_elementMapList.append(m_elemMap);

    // these will be exernal pins
    m_pinMap.insert("n1", new ECNode(ownerCircuit, m_elemMap->pin(0)));
    m_pinMap.insert("p1", new ECNode(ownerCircuit, m_elemMap->pin(1)));

    Property * r = new Property("resistance", Variant::Type::Double);
	r->setCaption(tr("Resistance"));
	r->setUnit(QChar(0x3a9));
	r->setValue(1);
	r->setMinValue(1e-6);
    addProperty(r);

    ownerCircuit.addComponent(this);
}

Resistor::~Resistor() {
    circuit().removeComponent(this);
}

void Resistor::propertyChanged(Property& theProperty, QVariant newValue, QVariant oldValue)
{
    Q_ASSERT(theProperty.name() == "resistance");
    Q_ASSERT(newValue.toDouble() > 0);

    Q_UNUSED(oldValue);

    m_resistance->setResistance(newValue.toDouble());
}

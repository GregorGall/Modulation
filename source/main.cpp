#include "LabSource.h"
#include "ConsoleGraph.h"

int main() {

	/* ѕараметры генератора */
	double carrier = 13e6;
	double period = 1 / carrier;
	double timePoint1 = 0;
	double timePoint2 = 100 * period;

	/* ѕростой синусоидальный сигнал */
	LabSource plainSin(timePoint1, timePoint2, carrier);							// »нициализаци€ генератора сигнала
	plainSin.setRange(0.5 * carrier, 1.5 * carrier);								// ”становка границ преобразовани€ ‘урье
	auto u1 = plainSin.sin().getValue();
	auto s1 = plainSin.cmFT().getValue(Format::ABS);

	/* јмплитудна€ модул€ци€ синусом */
	LabSource amSin(timePoint1, timePoint2, carrier);
	amSin.setRange(0.5 * carrier, 1.5 * carrier);
	amSin.setModParameters({ getSinMod(timePoint2, 5), Modulation::AMP, 0.5 });		// { указатель на мод.функцию, тип модул€ции, глубина модул€ции }
	auto u2 = amSin.sin().getValue();
	auto s2 = amSin.cmFT().getValue(Format::ABS);

	/* „астотна€ модул€ци€ синусом */
	LabSource fmSin(timePoint1, timePoint2, carrier);
	fmSin.setRange(0.5 * carrier, 1.5 * carrier);
	fmSin.setModParameters({ getSinMod(timePoint2, 5), Modulation::FRQ, 0.2*carrier });
	auto u3 = fmSin.sin().getValue();
	auto s3 = fmSin.cmFT().getValue(Format::ABS);

	/* ‘азова€ модул€ци€ синусом */
	LabSource pmSin(timePoint1, timePoint2, carrier);
	pmSin.setRange(0.5 * carrier, 1.5 * carrier);
	pmSin.setModParameters({ getSinMod(timePoint2, 5), Modulation::PH, 1 });
	auto u4 = pmSin.sin().getValue();
	auto s4 = pmSin.cmFT().getValue(Format::ABS);


	/* ќтрисовка графиков */
	ConsoleGraph graph(750, 450, {4, 2});
	graph.plot(u1);
	graph.plot(s1, 1, 2);
	graph.plot(u2, 2, 1);
	graph.plot(s2, 2, 2);
	graph.plot(u3, 3, 1);
	graph.plot(s3, 3, 2);
	graph.plot(u4, 4, 1);
	graph.plot(s4, 4, 2);


	return 0;
}
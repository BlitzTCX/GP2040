/**
 * GP2040 Configurator Development Server
 */

const express = require('express');
const cors = require('cors');

const controllers = require('../src/Data/Controllers.json');

const port = process.env.PORT || 8080;
const baseButtonMappings = {
	Up:    { pin: -1, error: null },
	Down:  { pin: -1, error: null },
	Left:  { pin: -1, error: null },
	Right: { pin: -1, error: null },
	B1:    { pin: -1, error: null },
	B2:    { pin: -1, error: null },
	B3:    { pin: -1, error: null },
	B4:    { pin: -1, error: null },
	L1:    { pin: -1, error: null },
	R1:    { pin: -1, error: null },
	L2:    { pin: -1, error: null },
	R2:    { pin: -1, error: null },
	S1:    { pin: -1, error: null },
	S2:    { pin: -1, error: null },
	L3:    { pin: -1, error: null },
	R3:    { pin: -1, error: null },
	A1:    { pin: -1, error: null },
	A2:    { pin: -1, error: null },
};

const app = express();
app.use(cors());
app.use(express.json());

app.get('/api/resetSettings', (req, res) => {
	console.log('/api/resetSettings');
	return res.send({ success: true });
});

app.get('/api/getGamepadOptions', (req, res) => {
	console.log('/api/getGamepadOptions');
	return res.send({
		dpadMode: 0,
		inputMode: 1,
		socdMode: 2,
	});
});

app.get('/api/getLedOptions', (req, res) => {
	console.log('/api/getLedOptions');
	return res.send({
		brightnessMax: 255,
		brightnessSteps: 5,
		ledFormat: 0,
		ledLayout: 1,
		ledsPerPixel: 2,
		dpadUp: 0,
		dpadDown: 1,
		dpadLeft: 2,
		dpadRight: 3,
		buttonB1: 4,
		buttonB2: 5,
		buttonB3: 6,
		buttonB4: 7,
		buttonL1: 8,
		buttonR1: 9,
		buttonL2: 10,
		buttonR2: 11,
		buttonS1: null,
		buttonS2: null,
		buttonL3: null,
		buttonR3: null,
		buttonA1: null,
		buttonA2: null,
	});
});

app.get('/api/getPinMappings', (req, res) => {
	console.log('/api/getPinMappings');
	let mappings = { ...baseButtonMappings };
	for (let prop of Object.keys(controllers['pico'])) {
		if (mappings[prop])
			mappings[prop] = parseInt(controllers['pico'][prop]);
	}

	return res.send(mappings);
});

app.post('/api/setGamepadOptions', (req, res) => {
	console.log('/api/setGamepadOptions');
	return res.send(req.body);
});

app.post('/api/setLedOptions', (req, res) => {
	console.log('/api/setLedOptions');
	return res.send(req.body);
});

app.post('/api/setPinMappings', (req, res) => {
	console.log('/api/setPinMappings');
	return res.send(req.body);
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
});
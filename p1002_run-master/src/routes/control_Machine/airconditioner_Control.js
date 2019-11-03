import express from 'express'
const http = require('http');
const router = express.Router();

const hostname = '192.168.0.9'
const port = '3000'
const path = '/AirconditionerControl/'

let pi_server_Url = {
    //hostname: '192.168.0.9,
    hostname: '192.168.1.84',
    port: '3000',
    path : '/AirconditionerControl/'
};

router.post('/power', (req, res, next) => {
    const aa = {};
    console.log('Airconditioner power');
    pi_server_Url.path += "power";
    http.request(pi_server_Url).end();
    pi_server_Url.path = '/AirconditionerControl/';
    res.json(aa);
});

router.post('/speed', (req, res, next) => {
    const aa = {};
    console.log('Airconditioner speed');
    pi_server_Url.path += "speed";
    http.request(pi_server_Url).end();
    pi_server_Url.path = '/AirconditionerControl/';
    res.json(aa);
});

router.post('/tempUp', (req, res, next) => {
    const aa = {};
    console.log('Airconditioner tempup');
    pi_server_Url.path += "tempup";
    http.request(pi_server_Url).end();
    pi_server_Url.path = '/Airconditioner_Control/';
    res.json(aa);
});

router.post('/tempDown', (req, res, next) => {
    const aa = {};
    console.log('Airconditioner tempdown');
    pi_server_Url.path += "tempdown";
    http.request(pi_server_Url).end();
    pi_server_Url.path = '/Airconditioner_Control/';
    res.json(aa);
});

router.post('/:action', (req, res, next) => {
    console.log(`airconditioner ${req.params.action}`);
    http.request({
        hostname,
        port,
        path: path + req.params.action
    }).end();
    console.log(path + req.params.action);
    res.json({});
});

module.exports = router;
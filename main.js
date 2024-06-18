const { app, BrowserWindow, ipcMain } = require('electron');
const { spawn } = require('child_process');
const path = require('path');

let mainWindow;

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1200,
        height: 900,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false
        }
    });

    mainWindow.loadFile('index.html');

}

app.on('ready', createWindow);

ipcMain.on('runScheduler', (event, { algorithm, input }) => {
    console.log('Received runScheduler event with algorithm:', algorithm);
    console.log('Input:', input);

    const exe = spawn('./scheduler.exe', [algorithm, input]);

    exe.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
        try {
            let result = JSON.parse(data);
            console.log("Output received:");
            console.log(result);
            event.sender.send('schedulerResult', { result });
        } catch (error) {
            console.error('Error parsing JSON:', error.message);
            event.sender.send('schedulerResult', { error: 'Error parsing JSON' });
        }
    });

    exe.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
        event.sender.send('schedulerResult', { error: data.toString() });
    });

    exe.on('close', (code) => {
        console.log(`child process exited with code ${code}`);
        if (code !== 0) {
            console.error(`Process exited with code ${code}`);
            event.sender.send('schedulerResult', { error: `Process exited with code ${code}` });
        }
    });

    exe.on('error', (err) => {
        console.error('Failed to start child process:', err);
        event.sender.send('schedulerResult', { error: err.message });
    });
});
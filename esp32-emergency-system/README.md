# ESP32 Emergency Alert System

Real-time emergency alert system using ESP32 FSR sensors, WebSocket communication, and hospital dashboards.

## Quick Deploy to Render

1. Push this repository to GitHub
2. Create a new Web Service on Render
3. Connect your GitHub repository
4. Render will automatically detect the configuration
5. Deploy!

## Configuration

- Build Command: `npm install`
- Start Command: `npm start`
- Environment: Node

## Local Development

```bash
npm install
npm start
```

Server runs on port 3000 (or PORT environment variable)

## Access Points

- `/` - Home page with links
- `/carDriver.html` - Driver interface
- `/hospital1.html` - Hospital 1 dashboard
- `/hospital2.html` - Hospital 2 dashboard
- `/hospital3.html` - Hospital 3 dashboard

## API Endpoints

- `POST /api/fsr-trigger` - ESP32 sensor trigger endpoint
- `GET /api/health` - Health check endpoint

## ESP32 Configuration

Update your ESP32 code with the deployed URL:
```cpp
const char* serverUrl = "https://your-app.onrender.com/api/fsr-trigger";
```

# ESP32 Emergency System - Project Structure

## Root Files
- `server.js` - Main Express server with WebSocket support
- `package.json` - Node.js dependencies and scripts
- `README.md` - Project documentation
- `DEPLOY.md` - Deployment instructions for Render
- `.gitignore` - Git ignore rules

## Folders

### `/public` - Frontend Files (Served Statically)
All HTML, CSS, and JavaScript files for the web interface:
- `carDriver.html` - Driver interface
- `carDriver.js` - Driver logic
- `hospital1.html` - Hospital 1 dashboard
- `hospital2.html` - Hospital 2 dashboard
- `hospital3.html` - Hospital 3 dashboard
- `hospitalDashboard.js` - Hospital dashboard logic
- `hospitalDashboard.css` - Hospital dashboard styles
- `styles.css` - Driver interface styles

### `/esp32` - Arduino Code
ESP32 sensor code (not deployed to web):
- `esp32_fsr_sensor.ino` - Basic FSR sensor code
- `esp32_fsr_gps_sensor.ino` - FSR with GPS tracking

## Key Changes Made

1. ✅ Moved `server.js` and `package.json` to root
2. ✅ Created `/public` folder for all frontend files
3. ✅ Updated server to serve static files from `/public`
4. ✅ Fixed WebSocket connections to use relative URLs (`io()` instead of `io('http://localhost:3000')`)
5. ✅ Removed all unnecessary documentation files
6. ✅ Deleted old `backend`, `NewBackend`, and `frontend` folders
7. ✅ Simplified package.json (removed unused dependencies)
8. ✅ Added proper `.gitignore`

## How It Works

1. Server runs on port 3000 (or PORT env variable)
2. Static files served from `/public` folder
3. WebSocket connections for real-time communication
4. ESP32 posts to `/api/fsr-trigger` endpoint
5. Server broadcasts alerts to connected clients

## Deployment Ready ✅

This structure is now ready for:
- Render deployment
- Heroku deployment
- Any Node.js hosting platform
- Docker containerization

The "Cannot GET /carDriver.html" error is fixed because:
- Files are in `/public` folder
- Server uses `express.static(path.join(__dirname, 'public'))`
- All paths are relative and work in production

# Deployment Guide for Render

## Step 1: Push to GitHub

```bash
git init
git add .
git commit -m "Initial commit - ESP32 Emergency System"
git branch -M main
git remote add origin YOUR_GITHUB_REPO_URL
git push -u origin main
```

## Step 2: Deploy on Render

1. Go to [render.com](https://render.com) and sign in
2. Click "New +" and select "Web Service"
3. Connect your GitHub repository
4. Configure:
   - Name: `esp32-emergency-system` (or your choice)
   - Environment: `Node`
   - Build Command: `npm install`
   - Start Command: `npm start`
   - Instance Type: Free
5. Click "Create Web Service"

## Step 3: Access Your App

Once deployed, Render will give you a URL like:
`https://esp32-emergency-system.onrender.com`

Access points:
- `https://your-app.onrender.com/` - Home page
- `https://your-app.onrender.com/carDriver.html` - Driver interface
- `https://your-app.onrender.com/hospital1.html` - Hospital 1
- `https://your-app.onrender.com/hospital2.html` - Hospital 2
- `https://your-app.onrender.com/hospital3.html` - Hospital 3

## Step 4: Update ESP32 Code

Update your ESP32 Arduino code with the deployed URL:

```cpp
const char* serverUrl = "https://your-app.onrender.com/api/fsr-trigger";
```

## Troubleshooting

If you get "Cannot GET /carDriver.html":
- Check that the `public` folder exists with all HTML files
- Verify `server.js` has: `app.use(express.static(path.join(__dirname, 'public')));`
- Check Render logs for any errors

## Local Testing

Before deploying, test locally:

```bash
npm install
npm start
```

Then open: `http://localhost:3000/carDriver.html`

# Configressif

> This project is under development through these plans:  
> _Written by sDenizOzturk via ChatGPT_

---

## plan-6 (21:31 21.07.2025)

### 🧭 Goal

Modularize the C++ source structure and introduce a cleaner HTTP routing system using dedicated route classes.
Also, define the future direction for authentication and system-level control endpoints.

---

### ✅ Completed

#### 📁 Source Structure Refactor

- Restructured `lib/configressif/` into modular directories:

  - `network/`, `ntp/`, `storage/`, `system/`, `utils/`, `http/`

- Moved `accesspoint.*` into `network/accesspoint/`
- Kept `configressif.cpp/h` at the top level as the public entry point

#### 🌐 HTTP Route Separation

- Simplified existing `HttpServer` to focus only on:

  - Starting the server
  - Serving static files

- Extracted endpoint logic into dedicated route classes:

  - `NtpRoutes` handles `/api/ntp`
  - `NetworkRoutes` handles `/api/network`

- Each route class receives `AsyncWebServer&` via constructor injection
- All route logic is now modular and bound explicitly through `setup()`

---

### 🧭 Future Work

#### 🔐 Issue #13: [Add Authentication Middleware and Frontend Login UI](https://github.com/sDenizOzturk/configressif/issues/13)

- Protect all API routes with password-based login
- `POST /api/auth/login` endpoint to authenticate users
- Store password in NVS; initial password from `/default/auth.json`
- Frontend login page (`/login`) with global auth state
- Dummy-server support for testing

#### ⚙️ Issue #14: [Add System Settings API & UI (Restart, Factory Reset, Password Change)](https://github.com/sDenizOzturk/configressif/issues/14)

- System routes under `/api/system/*`:
- Restart, factory reset, password change, optional system info
- Frontend system page with confirmation buttons
- All actions require authentication
- Integration with `RestartManager`, `AuthManager`, and `StorageManager`

---

### plan-5 (23:35 20.07.2025)

#### 🧭 **Goal**

Implement default config bootstrap from SPIFFS to NVS on first boot or after factory reset.

#### ✅ **Core Features**

- Implemented default configuration loaders:

  - `network.json` → saved to NVS via `NetworkStorage`
  - `ntp.json` → saved to NVS via `NtpStorage`
  - `access-point.json` → loaded into memory (not saved)

- All default JSONs are stored inside `/default/` in SPIFFS

- Created the following config classes:

  - `NetworkConfig` with singleton access, getters/setters, NVS sync
  - `NtpConfig` with singleton access and initialization guard
  - `AccessPointConfig` with runtime-only parameters (read-only, SPIFFS-only)

- Added `StorageManager::init()` which:

  - Mounts SPIFFS
  - Reads from SPIFFS on first boot
  - Persists default configs to NVS
  - Writes an `initialized` flag to NVS

- Added debug output for config loading steps and fallbacks

- Introduced optional `DebugUtils::countdown()` for boot-time debugging

- Factory reset system partially planned (low-level clearAll, clearFullStorage drafted, not exposed yet)

---

## plan-4 (15:33 18.07.2025)

### 🧭 Goal

Add support for configuring **NTP (Network Time Protocol)** settings via the web interface.
Users will be able to specify an NTP server and timezone offset. These values will be stored in NVS and used to set the internal clock.

#### ✅ Core Features

- NTP config UI and API (see details above)
- C++/backend NTP integration
- Playwright tests and dummy-server support

#### 🛡️ **Additional Improvements**

- Async loading guard refactor with `useMultiLoading`, `firstValuesFetched`
- Bugfix: uncontrolled select/input, -12 offset issue
- Static DNS for static IP mode
- Improved debug/serial logging (network/DNS/NTP)
- API/data model sync: dummy-server, backend, frontend

---

## plan-3 (20:11 17.07.2025)

### ✅ Added

- Created a new branch: `feature/wifi-config`
- Developed a complete **Network Settings Page** with the following fields:

  - `wifiEnabled` (checkbox)
  - `ssid` (text)
  - `password` (password)
  - `dhcpEnabled` (checkbox)
  - `ip`, `gateway`, `subnet` (conditional text inputs)

- Implemented dynamic field visibility:

  - All fields are hidden unless `wifiEnabled` is true
  - `ip`, `gateway`, `subnet` are shown only if `dhcpEnabled` is false

- Validation rules:

  - IP address validation via reusable `IP_ADDRESS_RULES`
  - Password must be 8–63 chars if not empty (WPA2/3)
  - SSID must be ≤ 32 characters, required if Wi-Fi is enabled

- Added automatic `gateway` and `subnet` prefill when IP is entered
- Implemented reusable components:

  - `FormTextInput`, `FormCheckbox`, `FormButton`

- Cleaned up base styles (`index.css`) and removed unused global CSS
- Created `utils/urls.ts` to determine API base path dynamically (based on dev/prod)
- Created a dummy backend (`dummy-server`) using Express + TypeScript:

  - Routes defined in `routes/`, handlers in `controller/`
  - Supports GET/POST to `/network` for simulated data exchange
  - Added `concurrently`, `ts-node`, `nodemon` for development

- Frontend fetches initial data from dummy backend using `useEffect`
- Submit button POSTs the full form to the dummy backend
- CORS is enabled on the dummy server
- CI/CD-ready structure: backend and frontend can be run with a single command

### 🛠️ Next Planned Step

- Write end-to-end tests for network configuration
- Connect with actual ESP32 backend via `/network`
- Sync NVS read/write with C++ HTTP handlers
- Auto-deploy dummy-server + React via CI

---

## plan-2 (13:45 13.07.2025)

-

### ✅ Added

- A minimal **React + TypeScript** UI was created using Vite

- UI includes two main buttons: “Device Settings” and “Network Settings”

- React app is configured to build into workbench/data/configressif/

- A new **PlatformIO** project (workbench/) was added to test the integration

- Firmware now:

  - Starts in **Access Point mode** by default
  - Serves the UI from SPIFFS (data/ directory)

- The configressif library is placed inside workbench/lib/configressif and compiled locally

- SPIFFS mount and HTTP serving are now functional

- ⚠️ **C++ source code is now written inside workbench/ only.**
  The root /lib/configressif and /data/ folders will be populated **automatically via CI/CD**.

### 🛠️ Next Planned Step (issue-2)

- **CI/CD** integration:

  - Automatically copy workbench/lib/configressif → /lib/configressif
  - Automatically copy workbench/data → /data
  - Verify that files are correctly copied (e.g., via test or checksum)
  - Run frontend lint/build steps before final copy

---

## plan-1 (18:24 12.07.2025)

### 🧭 What is Configressif?

**Configressif** is a zero-boilerplate, web-based configuration framework for ESP32 devices.  
It allows developers to create customizable configuration flows using simple JSON files — with no need to write frontend or backend code.

- Web-based config panel is auto-generated
- Wi-Fi setup is built-in (no need to define it)
- Multilingual UI support is included out of the box
- Works even if the user only uploads the `data/` folder (SPIFFS)
- Requires just a single call on the firmware side: `configressif.init();`

---

### 🚀 Key Features

- ⚡ **One-line firmware integration**: `configressif.init();` handles everything
- 🌐 **Automatic Wi-Fi provisioning**: Connects via saved credentials or enters AP mode
- 📦 **JSON-based configuration**: Define custom device options via `options.json`
- 🌍 **Built-in multilingual UI**: Language files and language logic are embedded
- 🧠 **No need to write UI or server code**: The library auto-generates REST endpoints
- 🔁 **Settings are persisted** in NVS (ESP32), with EEPROM fallback planned
- ✅ **Predefined defaults**: Works out-of-the-box with the provided `data/` folder

---

### 📁 Project Structure

```

Configressif/
├── src/                  ← ESP32 C++ firmware code
│   └── configressif.h / .cpp
├── data/                 ← SPIFFS contents (prebuilt UI)
│   ├── options.json      ← Device parameters (editable by the user)
│   ├── ui.json           ← Theme, language, layout
│   └── logo.png          ← (Optional) user-defined logo
├── frontend/             ← React or Vanilla UI project
│   └── (builds into data/)
├── examples/             ← Firmware usage examples
└── README.md

```

---

### ⚙️ How It Works

1. The device boots and runs `configressif.init();`
2. The library:
   - Mounts SPIFFS
   - Loads Wi-Fi credentials (from NVS)
   - Connects to Wi-Fi (or falls back to AP mode)
   - Serves the web UI
3. The user configures custom parameters defined in `options.json`
4. The firmware uses `config.getOption("my_param")` to retrieve values

---

### 📂 `options.json`

This is where users define their **device-specific** parameters.  
You do **not** define Wi-Fi or language settings here — those are embedded.

Example:

```json
[
  {
    "key": "trigger_delay",
    "label": {
      "en": "Trigger Delay (ms)",
      "tr": "Tetikleme Süresi (ms)"
    },
    "type": "number",
    "default": 2000,
    "required": true
  },
  {
    "key": "device_name",
    "label": {
      "en": "Device Name",
      "tr": "Cihaz Adı"
    },
    "type": "string",
    "default": "Sensor-001"
  }
]
```

#### Supported Fields:

- `key`: Unique identifier (used in firmware)
- `label`: Multilingual label object
- `type`: `string`, `number`, `boolean`, `password`, `select`, etc.
- `default`: Optional default value
- `required`: If `true`, user must provide this before saving

---

### 🎨 `ui.json`

Controls UI behavior and theming.

```json
{
  "theme": "dark",
  "primaryColor": "#007bff",
  "languages": {
    "allowed": ["en", "tr", "de"],
    "primary": "en"
  }
}
```

- `logo.png` is embedded into the UI by default
- Users can override it by placing a file named `logo.png` into the `data/` folder
- Language selection is **automatic**:

  - If browser language is in `allowed`, it is used
  - Otherwise, `primary` language is used

---

### 💾 Defaults & Headless Boot

- The library comes with a default `data/` folder
- If the user **just uploads this folder** to SPIFFS and flashes the firmware, the device will:

  - Connect to Wi-Fi (or start AP mode)
  - Load language files
  - Serve a complete configuration UI
  - Apply `options.json` values

- No additional setup is required

---

### 📡 AP Mode Config

If no valid Wi-Fi credentials exist in NVS:

- The device enters **Access Point mode**
- It uses default values from an embedded internal config
  (e.g., `ap_ssid`, `ap_password`, `ap_ip`)
- These values are not user-configurable via JSON, but can be edited in firmware

---

### 🧪 Firmware Usage Example

```cpp
#include <Configressif.h>

Configressif config;

void setup() {
  config.init(); // One line to handle everything
}

void loop() {
  int delay = config.getOption("trigger_delay").asInt();
  String name = config.getOption("device_name").asString();
}
```

---

### 📋 Build & Deploy

You do **not** need to build the frontend manually.
The compiled UI is automatically generated via **CI/CD** when the developers update the React code.

The contents of the web UI are prebuilt and stored inside:

```
/data/configressif/
```

You can directly upload this folder to SPIFFS without using `npm` or building anything.

#### SPIFFS Upload:

- **PlatformIO:**

  ```bash
  pio run -t uploadfs
  ```

- **Arduino IDE:**
  Use the "ESP32 Sketch Data Upload" tool

---

CI/CD ensures that:

- All UI tests are executed before deployment
- The final build is always clean and up to date
- End users never need to install Node.js or run `npm`

---

### 🧱 Platform Support

| Platform | Status              |
| -------- | ------------------- |
| ESP32    | ✅ Full Support     |
| ESP8266  | 🛠️ Planned (via PR) |

ESP32 is the primary target. ESP8266 support may be added through future pull requests and simplified UI variants.

---

### ✨ Why “Configressif”?

“Config” + “Espressif”
→ A configuration framework designed specifically for Espressif microcontrollers like ESP32 and ESP8266.

---

### 🤝 Contributing

Contributions are welcome — especially for:

- ESP8266 support
- UI animations & presets
- Testing framework
- JSON Schema validation

---

_Project authored by [sDenizOzturk](https://github.com/sDenizOzturk), assisted via ChatGPT._

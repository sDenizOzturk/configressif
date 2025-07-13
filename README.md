# Configressif

> This project is under development through these plans:  
> _Written by sDenizOzturk via ChatGPT_

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

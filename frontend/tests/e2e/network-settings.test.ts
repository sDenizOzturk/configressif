import { test, expect } from "@playwright/test";

test("Only Use WIFI is visible by default", async ({ page }) => {
  await page.goto("/network");

  await expect(page.getByLabel("Use WIFI")).toBeVisible();

  await expect(page.getByLabel("SSID")).toHaveCount(0);
  await expect(page.getByLabel("Password")).toHaveCount(0);
  await expect(page.getByLabel("Use DHCP")).toHaveCount(0);
});

test("DHCP enabled: IP fields should be hidden", async ({ page }) => {
  await page.goto("/network");

  await page.getByLabel("Use WIFI").check();
  await page.getByLabel("Use DHCP").check();

  // IP-related fields should not exist
  await expect(page.getByLabel("Static IP Address")).toHaveCount(0);
  await expect(page.getByLabel("Gateway")).toHaveCount(0);
  await expect(page.getByLabel("Subnet Mask")).toHaveCount(0);
});

test("Typing IP address triggers auto-fill for Gateway and Subnet", async ({
  page
}) => {
  await page.goto("/network");

  await page.getByLabel("Use WIFI").check();
  await page.getByLabel("Use DHCP").uncheck();

  const ipInput = page.getByLabel("Static IP Address");
  const gatewayInput = page.getByLabel("Gateway");
  const subnetInput = page.getByLabel("Subnet Mask");

  await ipInput.fill("192.168.4.42");
  await ipInput.blur(); // trigger handleIpBlur()

  await expect(gatewayInput).toHaveValue("192.168.4.1");
  await expect(subnetInput).toHaveValue("255.255.255.0");
});

test("Full form submission with static IP reflects after reload", async ({
  page
}) => {
  await page.goto("/network");

  await page.getByLabel("Use WIFI").check();

  await page.getByLabel("SSID").fill("TestSSID");
  await page.getByLabel("Password").fill("pass123456");

  await page.getByLabel("Use DHCP").uncheck();

  await page.getByLabel("Static IP Address").fill("192.168.1.42");

  await page.getByRole("button", { name: "Save" }).click();

  // Wait shortly to ensure POST is processed
  await page.waitForTimeout(100);

  // Reload page to trigger fetch from backend
  await page.reload();

  // Form fields should reflect saved data
  await expect(page.getByLabel("Use WIFI")).toBeChecked();
  await expect(page.getByLabel("SSID")).toHaveValue("TestSSID");
  await expect(page.getByLabel("Password")).toHaveValue("pass123456");
  await expect(page.getByLabel("Use DHCP")).not.toBeChecked();
  await expect(page.getByLabel("Static IP Address")).toHaveValue(
    "192.168.1.42"
  );
  await expect(page.getByLabel("Gateway")).toHaveValue("192.168.1.1");
  await expect(page.getByLabel("Subnet Mask")).toHaveValue("255.255.255.0");
});

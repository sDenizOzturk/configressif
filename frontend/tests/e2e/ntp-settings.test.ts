import { test, expect } from "@playwright/test";

test.describe.serial("NTP Settings Page", () => {
  let ntpServers: { label: string; value: string }[];
  let timezoneOffsets: { label: string; value: number }[];

  test.beforeAll(async ({ request }) => {
    const [srvRes, tzRes] = await Promise.all([
      request.get("/configs/ntp-servers.json"),
      request.get("/configs/timezone-offsets.json")
    ]);
    ntpServers = await srvRes.json();
    timezoneOffsets = await tzRes.json();
  });

  test("Only 'Enable NTP' checkbox is visible by default", async ({ page }) => {
    await page.goto("/ntp");
    await expect(page.getByLabel("Enable NTP")).toBeVisible();
    await expect(page.getByLabel("NTP Server")).toHaveCount(0);
    await expect(page.getByLabel("Timezone Offset")).toHaveCount(0);
  });

  test("Checking 'Enable NTP' reveals server + offset selects", async ({
    page
  }) => {
    await page.goto("/ntp");
    await page.getByLabel("Enable NTP").check();
    const serverSelect = page.getByLabel("NTP Server");
    const offsetSelect = page.getByLabel("Timezone Offset");
    await expect(serverSelect).toBeVisible();
    await expect(offsetSelect).toBeVisible();
    for (const { label } of ntpServers) {
      await expect(serverSelect).toContainText(label);
    }
    for (const { label } of timezoneOffsets) {
      await expect(offsetSelect).toContainText(label);
    }
  });

  test("Configuration persists after reload", async ({ page }) => {
    await page.goto("/ntp");

    await page.getByLabel("Enable NTP").check();

    const targetServer = ntpServers[4]; // just use 5th server in list
    const targetOffset = timezoneOffsets[5]; // e.g. 6th offset, any will do

    await page.getByLabel("NTP Server").selectOption(targetServer.value);

    await page
      .getByLabel("Timezone Offset")
      .selectOption(targetOffset.value.toString());

    await page.getByRole("button", { name: "Save" }).click();

    await page.waitForTimeout(100);

    await page.goto("/");
    await page.goto("/ntp");

    await page.waitForTimeout(100);

    await expect(page.getByLabel("Enable NTP")).toBeChecked();
    await expect(page.getByLabel("NTP Server")).toHaveValue(targetServer.value);
    await expect(page.getByLabel("Timezone Offset")).toHaveValue(
      String(targetOffset.value)
    );
  });
});

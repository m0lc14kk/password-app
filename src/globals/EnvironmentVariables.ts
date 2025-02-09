import { config } from "dotenv";
import { type DesktopAppModesType } from "./types/EnvironmentVariablesTypes";

config();

const DESKTOP_APP_MODE: DesktopAppModesType = (process.env.DESKTOP_APP_MODE || "development") as DesktopAppModesType;

export { DESKTOP_APP_MODE };
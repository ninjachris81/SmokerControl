package net.ninjachris81.smokercontrol;

public class SmokerData {

    private String connectedState = "Init";

    private String profileName = "No Profile";

    private float outsideTemp = 0f;
    private float outsideHumidity = 0f;
    private float insideTemp = 0f;
    private float meatTemp = 0f;

    private boolean isAutoStop = false;

    private float insideTargetTemp = 0f;
    private float meatTargetTemp = 0f;

    private long duration = 0;
    private String durationFormatted = "";

    public String getConnectedState() {
        return connectedState;
    }

    public void setConnectedState(String connectedState) {
        this.connectedState = connectedState;
    }

    public String getProfileName() {
        return profileName;
    }

    public void setProfileName(String profileName) {
        this.profileName = profileName;
    }

    public float getOutsideTemp() {
        return outsideTemp;
    }

    public void setOutsideTemp(float outsideTemp) {
        this.outsideTemp = outsideTemp;
    }

    public float getOutsideHumidity() {
        return outsideHumidity;
    }

    public void setOutsideHumidity(float outsideHumidity) {
        this.outsideHumidity = outsideHumidity;
    }

    public float getInsideTemp() {
        return insideTemp;
    }

    public void setInsideTemp(float insideTemp) {
        this.insideTemp = insideTemp;
    }

    public float getMeatTemp() {
        return meatTemp;
    }

    public void setMeatTemp(float meatTemp) {
        this.meatTemp = meatTemp;
    }

    public boolean isAutoStop() {
        return isAutoStop;
    }

    public void setAutoStop(boolean autoStop) {
        isAutoStop = autoStop;
    }

    public float getInsideTargetTemp() {
        return insideTargetTemp;
    }

    public void setInsideTargetTemp(float insideTargetTemp) {
        this.insideTargetTemp = insideTargetTemp;
    }

    public float getMeatTargetTemp() {
        return meatTargetTemp;
    }

    public void setMeatTargetTemp(float meatTargetTemp) {
        this.meatTargetTemp = meatTargetTemp;
    }

    public long getDuration() {
        return duration;
    }

    public void setDuration(long duration) {
        this.duration = duration;

        setDurationFormatted(duration < 60 ? duration + " sec"
                : duration >= 60 && duration < 3600 ? (duration / 60 + " min")
                : duration / 3600 + " h " + (duration % 3600) / 60 + " min");
    }

    public String getDurationFormatted() {
        return durationFormatted;
    }

    public void setDurationFormatted(String durationFormatted) {
        this.durationFormatted = durationFormatted;
    }
}

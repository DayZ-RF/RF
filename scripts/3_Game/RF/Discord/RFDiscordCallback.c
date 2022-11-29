// Discord Rest Callback
class RFDiscordCallback: RestCallback {

	// Callback delegate
	RFDiscordService delegate;

	// MARK: - Override

	override void OnError(int errorCode) {
		// 5 is a Discord errorCode describing that limit of requests is exceeded
		if (errorCode == 5) {
			delegate.LimitExceeded(this);
			return;
		}
		delegate.OnSuccess(this);
	}
}

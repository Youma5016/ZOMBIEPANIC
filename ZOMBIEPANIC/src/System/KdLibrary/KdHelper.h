#pragma once
/*
inline json11::Json LoadJson(const std::string& filename) {
	std::ifstream ifs(filename);
	if (!ifs) { return nullptr; }

	std::string strJson(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
			);

	//‰ğÍ
	std::string err;
	json11::Json jsonObj = json11::Json::parse(strJson, err);
	if (err.size() > 0) { return nullptr; }

	return jsonObj;
}
*/
// ˆÀ‘S‚ÉReleaseŠÖ”‚ğÀs‚·‚é
template<class T>
void KdSafeRelease(T*& p) {
	if (p) {
		p->Release();
		p = nullptr;
	}
}




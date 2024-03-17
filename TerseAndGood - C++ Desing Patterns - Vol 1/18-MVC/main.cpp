#include <iostream>
#include <vector>

// Model
class Model {
public:
  Model(std::vector<int> data): m_data(data) {}

  int get(size_t i) const {
    if(i < m_data.size())
      return m_data[i];
  }

  void update(size_t i, int d) {
    if(i < m_data.size())
      m_data[i] = d;
  }
private:
  std::vector<int> m_data;
};

// Controller
class Controller {
public:
  Controller(Model *model) : m_model(model) {
      this->m_startShow = 0;
      this->m_sizeShow = 3;
  }
  // show
  std::vector<int> get() const {
    std::vector<int> vec_show(m_sizeShow);
    for(size_t i = 0; i < vec_show.size(); i++)
      vec_show[i] = m_model->get(i+m_startShow);
    return vec_show;
  }

  void update_model(size_t i, int d) {
    m_model->update(i, d);
  }

  void update_startShow(size_t startShow) {
    m_startShow = startShow;
  }

  void update_sizeShow(size_t sizeShow) {
    m_sizeShow = sizeShow;
  }

private:
  Model *m_model = nullptr;
  size_t m_startShow;
  size_t m_sizeShow;
};

// view
class View {
public:
  View(Model *model) : m_controller(new Controller(model)) { }

  void show() const {
    std::vector<int> vec_show = m_controller->get();
    for (size_t i = 0; i < vec_show.size(); i++) {
      std::cout << vec_show[i] << ' ';
    }
    std::cout << std::endl;
  }

  void update_model(size_t i, int d) {
    m_controller->update_model(i, d);
  }

  void update_startShow(size_t startShow) {
    m_controller->update_startShow(startShow);
  }

  void update_sizeShow(size_t sizeShow) {
    m_controller->update_sizeShow(sizeShow);
  }

private:
  Controller *m_controller = nullptr;
};

int main() {

  std::vector<int> data;
  for (size_t i = 0; i < 100; i++) {
    /* code */
    data.push_back(i);
  }
  Model *model = new Model(data);
  View viewClient(model);

  viewClient.show();
  viewClient.update_startShow(4);
  viewClient.update_sizeShow(5);

  viewClient.show();
  viewClient.update_model(6, 66);
  viewClient.show();
  return 0;
}

import java.util.*;

public class FCFS implements Algorithm{

    private List<Task> taskList;

    public FCFS(List<Task> taskList){
        this.taskList = taskList;
    }

    public void schedule(){
        Task thisTask = pickNextTask();
        if(thisTask!=null){
            CPU.run(thisTask, thisTask.getBurst());
        }
    }

    public Task pickNextTask(){
        if(this.taskList.isEmpty()) return null;
        Task top = this.taskList.get(0);
        this.taskList.remove(0);
        return top;
    }
}
